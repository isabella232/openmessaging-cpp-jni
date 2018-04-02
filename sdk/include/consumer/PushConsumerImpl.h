#ifndef OMS_PUSH_CONSUMER_IMPL_H
#define OMS_PUSH_CONSUMER_IMPL_H

#include "Namespace.h"
#include "core.h"
#include "consumer/PushConsumer.h"
#include "ServiceLifecycleImpl.h"

BEGIN_NAMESPACE_3(io, openmessaging, consumer)

    class PushConsumerImpl : public virtual consumer::PushConsumer, public virtual ServiceLifecycleImpl {
    public:
        PushConsumerImpl(jobject proxy);

        virtual ~PushConsumerImpl();

        virtual KeyValuePtr attributes();

        virtual void resume();

        virtual void suspend(long timeout);

        virtual bool isSuspended();

        virtual consumer::PushConsumer& attachQueue(const std::string &queueName,
                                          const consumer::MessageListenerPtr &listener,
                                          const KeyValuePtr &properties);

        virtual consumer::PushConsumer& detachQueue(const std::string &queueName);

        virtual void addInterceptor(const consumer::PushConsumerInterceptorPtr &interceptor);

        virtual void removeInterceptor(const consumer::PushConsumerInterceptorPtr &interceptor);


    private:
        jclass classPushConsumer;
        jclass classMessageListenerAdaptor;

        jmethodID midProperties;
        jmethodID midResume;
        jmethodID midSuspend;
        jmethodID midIsSuspended;
        jmethodID midAttachQueue;
        jmethodID midDetachQueue;
    };

END_NAMESPACE_3(io, openmessaging, core)

#endif //OMS_PUSH_CONSUMER_IMPL_H
