# cpp_generator
# http
git config --global http.https://github.com.proxy http://127.0.0.1:7890
git config --global https.https://github.com.proxy https://127.0.0.1:7890

# socket
git config --global http.proxy 'socks5://127.0.0.1:7890'
git config --global https.proxy 'socks5://127.0.0.1:7890'



git config --global http.proxy 172.23.192.1:7890

git filter-branch --env-filter '
OLD_EMAIL="1002718237@qq.com"
CORRECT_EMAIL="921797341@qq.com"
if [ "$GIT_COMMITTER_EMAIL" = "$OLD_EMAIL" ]
then
    export GIT_COMMITTER_EMAIL="$CORRECT_EMAIL"
fi
if [ "$GIT_AUTHOR_EMAIL" = "$OLD_EMAIL" ]
then
    export GIT_AUTHOR_EMAIL="$CORRECT_EMAIL"
fi
' --tag-name-filter cat -- --branches --tags

git filter-branch -f --env-filter '
OLD_NAME="sxx"
CORRECT_NAME="fengzhaoyu"
if [ "$GIT_COMMITTER_NAME" = "$OLD_NAME" ]
then
    export GIT_COMMITTER_NAME="$CORRECT_NAME"
fi
if [ "$GIT_AUTHOR_NAME" = "$OLD_NAME" ]
then
    export GIT_AUTHOR_NAME="$CORRECT_NAME"
fi
' --tag-name-filter cat -- --branches --tags

git filter-branch --commit-filter '
    if [ "$GIT_COMMITTER_EMAIL" = "1002718237@qq.com" ];
    then
        GIT_COMMITTER_NAME="fengzhaoyu";
        GIT_AUTHOR_NAME="fengzhaoyu";
        GIT_COMMITTER_EMAIL="921797341@qq.com";
        GIT_AUTHOR_EMAIL="921797341@qq.com";
        git commit-tree "$@";
    else
        git commit-tree "$@";
    fi' HEAD