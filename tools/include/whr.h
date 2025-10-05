//#pragma once
#ifndef CFL_HEAD_TEMPLATE_DEFINE
#define CFL_HEAD_TEMPLATE_DEFINE
#include "dll_header.h"
#include <bits/stdc++.h>
#include <assert.h>
#include <winsock2.h>
#include <winsock.h>
#include <ws2tcpip.h>
#include<windows.h>
#include <conio.h>
#include <pthread.h>
#include <time.h>
using namespace std;
#define debug(x) cout << #x << ":" << x << endl
#define rep(i, x, n) for (int i = x; i <= n; i++)
#define dep(i, x, n) for (int i = x; i >= n; i--)
#define mem(a, x) memset(a, x, sizeof a)
typedef pair<int, int> pii;
#define ls (pos << 1)
#define rs ((pos << 1) | 1)
#define mid ((l + r) >> 1)
#define lowbit(x) ((x) & (-(x)))
//#define endl "\n"
#define __builtin_popcountll(x) popcount(x) //返回x的二进制中1的个数.
#define y1 y1__
#define y2 y2__
#define fir first
#define sec second
#define sz(s) (int)(s.size())
#define all(v) v.begin(),v.end()
#define pb push_back
#define mkp make_pair
#define sleep Sleep
#define cls system("cls")
#define strep(i,s) for(int i=0;i<sz(s);i++)
#define Min(x,y) x=min(x,y)
#define Max(x,y) x=max(x,y)
#define exp eexxpp
#define slp Sleep
#define iv inline void
#define pause system("pause")
typedef long long ll;
typedef unsigned long long ull;
typedef long double ldb;
typedef pair<ll, ll> pl;
#define White Color(0)
#define Blue Color(5)
#define Green Color(2)
#define Purple Color(3)
#define Red Color(4)
#define Cyan Color(1)
#define Yellow Color(6)
#define Gray Color(7)
#define COMMON 0x6DEF7E
#define UNUSUAL 0x5DE6FF
#define RARE 0xE3524D
#define EPIC 0xDE1F86
#define LEGENDARY 0x1F1FDE
#define MYTHIC 0xDEDB1F
#define ULTRA 0x752BFF
#define SUPER 0xA3FF2B

#endif
