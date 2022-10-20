﻿#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include "Winsock2.h"
#pragma comment(lib, "WS2_32.lib")

using namespace std;
string GetErrorMsgText(int code)
{
    string msgText;
    switch (code)
    {
    case WSAEINTR: msgText = "Работа функции прервана"; break;
    case WSAEACCES: msgText = "Разрешение отвергнуто"; break;
    case WSAEFAULT: msgText = "Ошибочный адрес"; break;
    case WSAEINVAL: msgText = "Ошибка в аргументе"; break;
    case WSAEMFILE: msgText = "Слишком много файлов открыто"; break;
    case WSAEWOULDBLOCK:msgText = "Ресурс временно недоступен"; break;
    case WSAEINPROGRESS:msgText = "Операция в процессе развития"; break;
    case WSAEALREADY:msgText = "Операция уже выполняется "; break;
    case WSAENOTSOCK:msgText = "Сокет задан неправильно"; break;
    case WSAEDESTADDRREQ:msgText = "Требуется адрес расположения "; break;
    case WSAEMSGSIZE:msgText = "Сообщение слишком длинное "; break;
    case WSAEPROTOTYPE:msgText = "Неправильный тип протокола для сокета "; break;
    case WSAENOPROTOOPT:msgText = "Ошибка в опции протокола"; break;
    case WSAEPROTONOSUPPORT:msgText = "Протокол не поддерживается "; break;
    case WSAESOCKTNOSUPPORT:msgText = "Тип сокета не поддерживается "; break;
    case WSAEOPNOTSUPP:msgText = "Операция не поддерживается "; break;
    case WSAEPFNOSUPPORT:msgText = "Тип протоколов не поддерживается "; break;
    case WSAEAFNOSUPPORT:msgText = "Тип адресов не поддерживается протоколом"; break;
    case WSAEADDRINUSE:msgText = "Адрес уже используется "; break;
    case WSAEADDRNOTAVAIL:msgText = "Запрошенный адрес не может быть использован"; break;
    case WSAENETDOWN:msgText = "Сеть отключена "; break;
    case WSAENETUNREACH:msgText = "Сеть не достижима"; break;
    case WSAENETRESET:msgText = "Сеть разорвала соединение"; break;
    case WSAECONNABORTED:msgText = "Программный отказ связи "; break;
    case WSAECONNRESET:msgText = "Связь восстановлена "; break;
    case WSAENOBUFS:msgText = "Не хватает памяти для буферов"; break;
    case WSAEISCONN:msgText = "Сокет уже подключен"; break;
    case WSAENOTCONN:msgText = "Сокет не подключен"; break;
    case WSAESHUTDOWN:msgText = "Нельзя выполнить send: сокет завершил работу"; break;
    case WSAETIMEDOUT:msgText = "Закончился отведенный интервал  времени"; break;
    case WSAECONNREFUSED:msgText = "Соединение отклонено  "; break;
    case WSAEHOSTDOWN:msgText = "Хост в неработоспособном состоянии"; break;
    case WSAEHOSTUNREACH:msgText = "Нет маршрута для хоста "; break;
    case WSAEPROCLIM:msgText = "Слишком много процессов "; break;
    case WSASYSNOTREADY:msgText = "Сеть не доступна "; break;
    case WSAVERNOTSUPPORTED:msgText = "Данная версия недоступна "; break;
    case WSANOTINITIALISED:msgText = "Не выполнена инициализация WS2_32.DLL"; break;
    case WSAEDISCON:msgText = "Выполняется отключение"; break;
    case WSATYPE_NOT_FOUND:msgText = "Класс не найден "; break;
    case WSAHOST_NOT_FOUND:msgText = "Хост не найден"; break;
    case WSATRY_AGAIN:msgText = "Неавторизированный хост не найден "; break;
    case WSANO_RECOVERY:msgText = "Неопределенная  ошибка "; break;
    case WSANO_DATA:msgText = "Нет записи запрошенного типа "; break;
    case WSA_INVALID_HANDLE:msgText = "Указанный дескриптор события  с ошибкой"; break;
    case WSA_INVALID_PARAMETER:msgText = "Один или более параметров с ошибкой"; break;
    case WSA_IO_INCOMPLETE:msgText = "Объект ввода-вывода не в сигнальном состоянии"; break;
    case WSA_IO_PENDING:msgText = "Операция завершится позже  "; break;
    case WSA_NOT_ENOUGH_MEMORY:msgText = "Не достаточно памяти "; break;
    case WSA_OPERATION_ABORTED:msgText = "Операция отвергнута "; break;
    case WSAEINVALIDPROCTABLE:msgText = "Ошибочный сервис "; break;
    case WSAEINVALIDPROVIDER:msgText = "Ошибка в версии сервиса "; break;
    case WSAEPROVIDERFAILEDINIT:msgText = "Невозможно инициализировать сервис "; break;
    case WSASYSCALLFAILURE:msgText = "Аварийное завершение системного вызова "; break;
    default: msgText = "??? UNKKOWN ERROR ???"; break;
    }
    return msgText;
}

string SetErrorMsgText(string msgText, int code)
{
    return msgText + GetErrorMsgText(code);
}

int main()
{
    SOCKET sS;
    WSADATA wsadata;
    try
    {
        while (true)
        {
            if (WSAStartup(MAKEWORD(2, 0), &wsadata) != 0)//подключение библиотеки
                throw SetErrorMsgText("Startup: ", WSAGetLastError());
            
            if ((sS = socket(AF_INET, SOCK_DGRAM, NULL)) == INVALID_SOCKET)//создание сокета
                throw SetErrorMsgText("Socket: ", WSAGetLastError());

            SOCKADDR_IN serv;
            serv.sin_family = AF_INET;
            serv.sin_port = htons(2000);
            serv.sin_addr.S_un.S_addr = INADDR_ANY;
            if (bind(sS, (LPSOCKADDR)&serv, sizeof(serv)) == SOCKET_ERROR)//связывают с параметрами
                throw SetErrorMsgText("Bind: ", WSAGetLastError());

            SOCKADDR_IN clnt;               //в нее автоматически  
            //помещаются параметры сокета клиента, после приема от него сообщения
            memset(&clnt, 0, sizeof(clnt));   
            int lc = sizeof(clnt);

            int  lb = 0;                    
            char ibuf[50];                  

            cout << "\nWaiting...\n" << endl;

            int message_counter = 0;

            do
            {
               // Sleep(50);
                if ((lb = recvfrom(sS, ibuf, sizeof(ibuf), NULL, (sockaddr*)&clnt, &lc)) == SOCKET_ERROR) //переводит программу 
                    //сервера в состояние ожидания, до поступления  сообщения от программы клиента (функция sendto).
                    throw  SetErrorMsgText("Recv: ", WSAGetLastError());

                cout << endl << ibuf << endl;    

               if ((lb = sendto(sS, ibuf, strlen(ibuf) + 1, NULL, (sockaddr*)&clnt, lc)) == SOCKET_ERROR)
                    throw  SetErrorMsgText("Send: ", WSAGetLastError());//
                //для пересылки клиентуу

                cout << message_counter++ << endl;

            } while (ibuf[0] != '\0');

            if (closesocket(sS) == SOCKET_ERROR)
                throw SetErrorMsgText("CloseSocket: ", WSAGetLastError());
            
            if (WSACleanup() == SOCKET_ERROR)
                throw SetErrorMsgText("Cleanup: ", WSAGetLastError());
        }
    }
    catch (string errorMsgText)
    {
        cout << endl << errorMsgText;
    }
}
