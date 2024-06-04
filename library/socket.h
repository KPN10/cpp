#ifndef SOCKET_H
#define SOCKET_H

#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/select.h>
#include <sys/poll.h>
#include <fcntl.h>
#include "print.h"

constexpr uint32_t Port = 55555;
constexpr uint32_t numberConnection = 1;
constexpr uint32_t bufSize = 1036;

class Socket
{
public:
    Socket()
    {
        printTrace(FUNCTION_NAME);
        sock = 0;
        addrSize = sizeof(addr);
        bzero(&addr, addrSize);
    }

    ~Socket()
    {
        printTrace(FUNCTION_NAME);
    }

    int SendData(uint8_t* xpData, uint32_t xLength) {
        return send(sock, xpData, xLength, 0);
    }
    int GetData(uint8_t* xpData, uint32_t xLength) {
        return recv(sock, xpData, xLength, 0);
    }

    void SetSocket(int xArg) { sock = xArg; }
    int GetSocket() { return sock; }

private:

protected:
    int sock;
    struct sockaddr_in addr;
    socklen_t addrSize;
};

class SocketServerSide : public Socket
{
public:
    SocketServerSide()
    {
        printTrace(FUNCTION_NAME);
    }

    ~SocketServerSide()
    {
        printTrace(FUNCTION_NAME);
    }

    int Init()
    {
        printTrace(FUNCTION_NAME);
        int ret;
        listener = socket(AF_INET, SOCK_STREAM, 0);
        if (listener < 0)
        {
            printError("%s error socket, listener: %d", FUNCTION_NAME, listener);
        }

        addr.sin_family = AF_INET;
        addr.sin_port = htons(Port);
        addr.sin_addr.s_addr = INADDR_ANY;

        int opt = 1;
        ret = setsockopt (listener, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
        if (ret == -1) {
            printError("%s error setcockopt, ret: %d", FUNCTION_NAME, ret);
            return -1;
        }

        unlink("127.0.0.1");
        ret = bind(listener, (struct sockaddr*)&addr, addrSize);
        if (ret < 0)
        {
            printError("%s error bind, ret: %d", FUNCTION_NAME, ret);
            return -1;
        }

        ret = listen(listener, numberConnection);
        if (ret < 0)
        {
            printError("%s error listen, ret: %d", FUNCTION_NAME, ret);
            return -1;
        }

        printTrace("%s socket wait...", FUNCTION_NAME);
        FD_ZERO(&rfds);
        FD_SET(listener, &rfds);
        uint32_t timeoutSeconds = 10;
        // struct timeval timeout;
        // timeout.tv_sec = (__time_t)timeoutSeconds;
        // timeout.tv_usec = 0;

        ret = select(listener + 1, &rfds, NULL, NULL, NULL);
        printTrace("select ret: %d", ret);
        if (ret == -1)
        {
            printError("%s error select, ret: %d", FUNCTION_NAME, ret);
            return -1;
        }
        else if (ret == 0)
        {
            printTrace("%s timeout occured (%d seconds)", FUNCTION_NAME, timeoutSeconds);
            return -1;
        }
        else
        {
            if (FD_ISSET(listener, &rfds))
            {
                sock = accept(listener, (struct sockaddr*)&addr, &addrSize);
                if (sock < 0) {
                    printError("%s error accept, sock: %d", FUNCTION_NAME, sock);
                    return -1;
                }
            }
        }

        // fcntl(listener, F_SETFL, O_NONBLOCK);
        
        isOpened = true;

        printTrace("__%s socket wait...", FUNCTION_NAME);
        return 0;
    }

    void Close()
    {
        FD_CLR(listener, &rfds);
        FD_ZERO(&rfds);

        if (listener)
        {
            printTrace("%s listener: 0x%llx", FUNCTION_NAME, listener);
            close(listener);
            listener = 0;
        }

        if (sock)
        {
            printTrace("%s sock: 0x%llx", FUNCTION_NAME, sock);
            close(sock);
        }

        isOpened = false;
    }

    // int AcceptClients()
    // {
        
    // }

    int Wait()
    {
        return 0;
    }

    bool IsOpened() { return isOpened; }

private:
    bool isOpened = false;
    int listener;

    fd_set rfds;

    struct pollfd fds;
};

class SocketClientSide : public Socket
{
public:
    SocketClientSide()
    {

    }

    ~SocketClientSide()
    {

    }

    int Init()
    {
        printTrace(FUNCTION_NAME);
        
        int ret;

        sock = socket(AF_INET, SOCK_STREAM, 0);
        if (sock < 0) {
            printError("%s socket, sock: %d", FUNCTION_NAME, sock);
            return -1;
        }

        addr.sin_family = AF_INET;
        addr.sin_port = htons(Port);
        addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

        ret = connect(sock, (struct sockaddr*)&addr, addrSize);
        if (ret < 0) {
            printError("%s connect, ret: %d", FUNCTION_NAME, ret);
            return -1;
        }

        isOpened = true;

        return 0;
    }

    void Close()
    {
        if (sock)
        {
            printTrace("%s, sock: %d", FUNCTION_NAME, sock);
            close(sock);
        } 

        isOpened = false;
    }

    bool IsOpened() { return isOpened; }

private:
    bool isOpened = false;
};

#endif

