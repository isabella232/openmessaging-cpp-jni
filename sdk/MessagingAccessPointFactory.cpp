#include "MessagingAccessPointFactory.h"
#include "MessagingAccessPointImpl.h"
#include "KeyValueImpl.h"

using namespace io::openmessaging;

MessagingAccessPoint*
getMessagingAccessPointImpl(const std::string &url, const NS::shared_ptr<KeyValue> &props) {

    Initialize();

    CurrentEnv current;
    const char* klassMessagingAccessPointFactory = "io/openmessaging/MessagingAccessPointFactory";
    jclass classMessagingAccessPointFactory = current.findClass(klassMessagingAccessPointFactory);
    jmethodID midGetMessagingAccessPoint;
    bool useKV = false;
    if (props) {
        useKV = true;
        std::string sig = buildSignature(Types::MessagingAccessPoint_, 2, Types::String_, Types::KeyValue_);
        midGetMessagingAccessPoint = current.getMethodId(classMessagingAccessPointFactory,
                                                         "getMessagingAccessPoint", sig.c_str(), true);
    } else {
        std::string sig = buildSignature(Types::MessagingAccessPoint_, 1, Types::String_);
        midGetMessagingAccessPoint = current.getMethodId(classMessagingAccessPointFactory,
                                                         "getMessagingAccessPoint", sig.c_str(), true);
    }

    jstring accessUrl = current.newStringUTF(url.c_str());

    jobject messagingAccessPoint;
    if (useKV) {
        NS::shared_ptr<KeyValueImpl> kv = NS::dynamic_pointer_cast<KeyValueImpl>(props);
        jobject prop = kv->getProxy();
        messagingAccessPoint = current.callStaticObjectMethod(classMessagingAccessPointFactory,
                                                              midGetMessagingAccessPoint,
                                                              accessUrl,
                                                              prop);
    } else {
        messagingAccessPoint = current.callStaticObjectMethod(classMessagingAccessPointFactory,
                                                              midGetMessagingAccessPoint,
                                                              accessUrl);
    }

    current.deleteRef(accessUrl);
    current.deleteRef(classMessagingAccessPointFactory);
    jobject globalRef = current.newGlobalRef(messagingAccessPoint);
    return new MessagingAccessPointImpl(url, props, globalRef);
}

NS::shared_ptr<MessagingAccessPoint>
MessagingAccessPointFactory::getMessagingAccessPoint(const std::string &url,
                                                     const NS::shared_ptr<KeyValue> &properties) {
    return NS::shared_ptr<MessagingAccessPoint>(::getMessagingAccessPointImpl(url, properties));
}

void MessagingAccessPointFactory::addInterceptor(
        const NS::shared_ptr<interceptor::MessagingAccessPointInterceptor> &interceptor) {

}

void MessagingAccessPointFactory::removeInterceptor(
        const NS::shared_ptr<interceptor::MessagingAccessPointInterceptor> &interceptor) {

}