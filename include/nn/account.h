/**
 * @file account.h
 * @brief Account service implementation.
 */

#pragma once

#include "os.h"
#include "types.h"

namespace nn {
namespace account {
typedef char Nickname[0x21];
typedef u64 NetworkServiceAccountId;

class AsyncContext;

class Uid {
public:
    u64 m_Storage[2];
};

class UserHandle {
public:
    Uid m_Uid;
    void* m_Handle;
};

void Initialize();
Result ListAllUsers(s32*, Uid*, s32 numUsers);
Result OpenUser(UserHandle*, Uid const&);
Result IsNetworkServiceAccountAvailable(bool* out, UserHandle const&);
void CloseUser(UserHandle const&);

Result EnsureNetworkServiceAccountAvailable(UserHandle const& userHandle);
Result EnsureNetworkServiceAccountIdTokenCacheAsync(AsyncContext*, UserHandle const&);
Result LoadNetworkServiceAccountIdTokenCache(u64*, char*, u64, UserHandle const&);

Result GetLastOpenedUser(Uid*);
Result GetNickname(Nickname* nickname, Uid const& userID);

Result GetUserId(Uid* uid, const UserHandle& handle);
Result OpenPreselectedUser(UserHandle* handle);

class AsyncContext {
public:
    AsyncContext();

    Result HasDone(bool*);
    Result GetResult();
    Result Cancel();
    Result GetSystemEvent(nn::os::SystemEvent*);
};
};  // namespace account
};  // namespace nn
