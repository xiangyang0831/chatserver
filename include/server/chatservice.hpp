#ifndef CHATSERVICE_H
#define CHATSERVICE_H
#include <unordered_map>
#include <functional>
#include <mutex>
#include "friendmodel.hpp"
#include "redis.hpp"
#include <usermodel.hpp>
#include <groupmodel.hpp>
#include <offlinemessagemodel.hpp>
#include <muduo/net/TcpConnection.h>
#include <json.hpp>
using namespace muduo;
using namespace std;
using namespace muduo::net;
using json = nlohmann::json;

// 表示处理消息的事件回调方法类型
using MsgHandler = std::function<void(const TcpConnectionPtr &conn, json js, Timestamp time)>;

// 聊天服务器业务类
class ChatService
{
public:
    // 获取单例对象的接口函数
    static ChatService *instance();

    // 处理登录业务
    void login(const TcpConnectionPtr &conn, json js, Timestamp time);

    // 处理注册业务
    void reg(const TcpConnectionPtr &conn, json js, Timestamp time);

    // 处理客户端异常退出
    void clientCloseEXception(const TcpConnectionPtr &conn);

    // 一对一聊天业务
    void oneChat(const TcpConnectionPtr &conn, json js, Timestamp time);

    // 添加好友业务
    void addFriend(const TcpConnectionPtr &conn, json js, Timestamp time);

    // 创建群组功能
    void creatGroup(const TcpConnectionPtr &conn, json js, Timestamp time);

    // 添加群组功能
    void addGroup(const TcpConnectionPtr &conn, json js, Timestamp time);

    // 群组聊天项目
    void groupChat(const TcpConnectionPtr &conn, json js, Timestamp time);

    // 处理注销业务
    void loginOut(const TcpConnectionPtr &conn, json js, Timestamp time);

    // redis处理业务
    void handleRedisSubscribeMessage(int,string);

    // 获取消息对应的处理器
    MsgHandler getHandler(int msgid);

    // 服务器异常后，重置方法
    void reset();

private:
    ChatService();
    // 存储消息id和其对应的事件处理方法
    unordered_map<int, MsgHandler> _msgHandlerMap;

    // 存储在线用户的通信连接
    unordered_map<int, TcpConnectionPtr> _userConnMap;

    // 定义互斥锁，保证_userConnMap的线程安全
    mutex _connMutex;

    // 数据操作类对象
    UserModel _userModel;

    // 离线消息
    OfflineMsgModel _offlineMsgModel;

    // 好友信息
    FriendModel _friendModel;

    // 群组信息
    GroupModel _groupModel;

    //redis对象
    Redis _redis;
};

#endif