#include <string>
#include <vector>

#include <boost/shared_ptr.hpp>
#include <gtest/gtest.h>

#include "MessagingAccessPoint.h"
#include "MessagingAccessPointFactory.h"
#include "KeyValueImpl.h"

TEST(MessagingAccessPointFactoryTest, testCtor) {
    using namespace io::openmessaging;
    using namespace std;

    string accessPointUrl = "oms:rocketmq://localhost:9876/default:default";
    string driverClassKey = "oms.driver.impl";
    string driverClass = "io.openmessaging.rocketmq.MessagingAccessPointImpl";

    Initialize();

    boost::shared_ptr<KeyValue> properties = boost::make_shared<KeyValueImpl>();
    properties->put(driverClassKey, driverClass);

    boost::shared_ptr<MessagingAccessPoint> messagingAccessPoint =
            MessagingAccessPointFactory::getMessagingAccessPoint(accessPointUrl, properties);

    boost::shared_ptr<producer::Producer> producer = messagingAccessPoint->createProducer();
    producer->startup();

    string topic = "TopicTest";
    vector<unsigned char> body;
    body.push_back('H');
    body.push_back('E');
    body.push_back('L');
    body.push_back('L');
    body.push_back('O');

    boost::shared_ptr<Message> message = producer->createByteMessageToTopic(topic, body);


    boost::shared_ptr<producer::SendResult> sendResult = producer->send(message);

    cout << sendResult->messageId() << endl;

}

TEST(MessagingAccessPointFactoryTest, testCreatePullConsumer) {
    using namespace io::openmessaging;
    using namespace std;

    string accessPointUrl = "oms:rocketmq://localhost:9876/default:default";
    string driverClassKey = "oms.driver.impl";
    string driverClass = "io.openmessaging.rocketmq.MessagingAccessPointImpl";

    Initialize();

    boost::shared_ptr<KeyValue> properties = boost::make_shared<KeyValueImpl>();
    properties->put(driverClassKey, driverClass);

    boost::shared_ptr<MessagingAccessPoint> messagingAccessPoint =
            MessagingAccessPointFactory::getMessagingAccessPoint(accessPointUrl, properties);
    std::string queueName("TopicTest");


    boost::shared_ptr<KeyValue> kv = boost::make_shared<KeyValueImpl>();
    const std::string key = "rmq.consumer.group";
    const std::string value = "OMS_CONSUMER";
    kv->put(key, value);

    boost::shared_ptr<consumer::PullConsumer> pullConsumer = messagingAccessPoint->createPullConsumer(queueName, kv);

    ASSERT_TRUE(pullConsumer);

    pullConsumer->startup();

    pullConsumer->shutdown();

//    while (true) {
//        boost::shared_ptr<Message> message = pullConsumer->poll();
//        if (message) {
//            boost::shared_ptr<KeyValue> kv = message->sysHeaders();
//            std::string msgId = kv->getString(BuiltinKeys::MessageId);
//            cout << "MessageId: " << msgId << endl;
//            pullConsumer->ack(msgId);
//        }
//
//    }
}