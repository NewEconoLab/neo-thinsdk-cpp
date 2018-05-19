#-------------------------------------------------
#
# Project created by QtCreator 2018-05-19T13:12:53
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = neo-thinsdk-cpp
CONFIG   += console
CONFIG   -= app_bundle

QMAKE_CXXFLAGS += -std=c++11

TEMPLATE = app

INCLUDEPATH += F:\code\coinapi\libbitcoin\include
INCLUDEPATH += F:\disk\iso\waykilib\boost_1_57_0
INCLUDEPATH += F:\code\neo-thinsdk-cpp
INCLUDEPATH += F:\code\neo-thinsdk-cpp\common
INCLUDEPATH += F:\code\neo-thinsdk-cpp\utils
INCLUDEPATH += F:\code\neo-thinsdk-cpp\neoseries
INCLUDEPATH += F:\disk\iso\waykilib\openssl-1.0.1g\include
INCLUDEPATH += F:\disk\iso\waykilib\scrypt-1.2.1


LIBS += F:\code\coinapi\debug\libcoinapi.a
LIBS += F:\disk\iso\waykilib\secp256k1\.libs\libsecp256k1.a
LIBS += F:\disk\iso\waykilib\boost_1_57_0\stage\lib\libboost_system-mgw48-1_57.a
LIBS += F:\disk\iso\waykilib\boost_1_57_0\stage\lib\libboost_date_time-mgw48-1_57.a
LIBS += F:\disk\iso\waykilib\boost_1_57_0\stage\lib\libboost_chrono-mgw48-1_57.a
LIBS += F:\disk\iso\waykilib\boost_1_57_0\stage\lib\libboost_filesystem-mgw48-1_57.a
LIBS += F:\disk\iso\waykilib\boost_1_57_0\stage\lib\libboost_iostreams-mgw48-1_57.a
LIBS += F:\disk\iso\waykilib\boost_1_57_0\stage\lib\libboost_locale-mgw48-mt-1_57.a
LIBS += F:\disk\iso\waykilib\boost_1_57_0\stage\lib\libboost_thread-mgw48-mt-1_57.a
LIBS += F:\disk\iso\waykilib\boost_1_57_0\stage\lib\libboost_program_options-mgw48-1_57.a
LIBS += F:\disk\iso\waykilib\boost_1_57_0\stage\lib\libboost_regex-mgw48-1_57.a
LIBS += F:\disk\iso\waykilib\boost_1_57_0\stage\lib\libboost_log-mgw48-1_57.a
LIBS += F:\disk\iso\waykilib\scrypt-1.2.1\libscrypt.a
LIBS += F:\disk\iso\waykilib\scrypt-1.2.1\libscrypt_sse2.a
LIBS += F:\disk\iso\waykilib\scrypt-1.2.1\libcperciva_aesni.a
LIBS += F:\disk\iso\waykilib\openssl-1.0.1g\libcrypto.a
LIBS += -lWs2_32 -lgdi32 -lwinmm -lwldap32 -lcrypt32


SOURCES += main.cpp \
    common/BaseCoinApi.cpp \
    common/BtcvoutForm.cpp \
    common/BtSeed.cpp \
    common/BtWallet.cpp \
    common/ChildNumber.cpp \
    common/coin_code.cpp \
    common/CommonCoinApi.cpp \
    common/CreateSignTransactionParams.cpp \
    common/KeyPath.cpp \
    common/Netparams.cpp \
    json/json_reader.cpp \
    json/json_value.cpp \
    json/json_writer.cpp \
    neoseries/helper.cpp \
    neoseries/neo_transaction.cpp \
    neoseries/NeoCreateSignTransactionParams.cpp \
    neoseries/NeoSeriesCoinApi.cpp \
    neoseries/ScriptBuilder.cpp \
    utils/bcmath_stl.cpp \
    utils/CoinType.cpp \
    utils/Common.cpp \
    utils/EncryptedData.cpp \
    utils/KeyCrypterScrpt.cpp \
    utils/SecureRandom.cpp \
    neoseries/ecc.c \
    neoseries/allocators.cpp \
    neoseries/uint256.cpp \
    neoseries/hash.cpp

HEADERS += \
    common/BaseCoinApi.hpp \
    common/BtcvoutForm.hpp \
    common/BtSeed.hpp \
    common/BtWallet.hpp \
    common/ChildNumber.hpp \
    common/coin_code.hpp \
    common/CommonCoinApi.hpp \
    common/CreateSignTransactionParams.hpp \
    common/KeyPath.hpp \
    common/Netparams.hpp \
    json/assertions.h \
    json/autolink.h \
    json/config.h \
    json/features.h \
    json/forwards.h \
    json/json.h \
    json/json_batchallocator.h \
    json/json_tool.h \
    json/reader.h \
    json/value.h \
    json/version.h \
    json/writer.h \
    neoseries/ecc.h \
    neoseries/helper.h \
    neoseries/neo_transaction.h \
    neoseries/NeoCreateSignTransactionParams.h \
    neoseries/NeoSeriesCoinApi.h \
    neoseries/OpCode.h \
    neoseries/ScriptBuilder.h \
    utils/bcmath_stl.h \
    utils/CoinType.h \
    utils/Common.h \
    utils/EncryptedData.h \
    utils/KeyCrypterScrypt.h \
    utils/SecureRandom.h \
    neoseries/allocators.h \
    neoseries/uint256.h \
    neoseries/hash.h
