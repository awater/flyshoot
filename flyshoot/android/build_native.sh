# set params
NDK_ROOT=/cygdrive/f/competition/kuso/android-ndk-r8b-windows/android-ndk-r8b
COCOS2DX_ROOT=/cygdrive/f/competition/kuso/cocos2d-1.0.1-x-0.12.0
GAME_ROOT=$COCOS2DX_ROOT/flyshootServer/flyshoot
GAME_ANDROID_ROOT=$GAME_ROOT/android
RESOURCE_ROOT=$GAME_ROOT/Resources

# make sure assets is exist
if [ -d $GAME_ANDROID_ROOT/assets ]; then
    rm -rf $GAME_ANDROID_ROOT/assets
fi

mkdir $GAME_ANDROID_ROOT/assets

# copy resources
for file in $RESOURCE_ROOT/*
do
    if [ -d $file ]; then
        cp -rf $file $GAME_ANDROID_ROOT/assets
    fi

    if [ -f $file ]; then
        cp $file $GAME_ANDROID_ROOT/assets
    fi
done

# build
$NDK_ROOT/ndk-build -C $GAME_ANDROID_ROOT $*

