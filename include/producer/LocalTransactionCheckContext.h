#ifndef OMS_LOCAL_TRANSACTION_CHECK_CONTEXT_H
#define OMS_LOCAL_TRANSACTION_CHECK_CONTEXT_H

#include "Namespace.h"

BEGIN_NAMESPACE_3(io, openmessaging, producer)

    class LocalTransactionCheckContext {
    public:
        virtual ~LocalTransactionCheckContext() {

        }

        virtual void commit() = 0;

        virtual void rollback() = 0;

    };

END_NAMESPACE_3(io, openmessaging, producer)

#endif //OMS_LOCAL_TRANSACTION_CHECK_CONTEXT_H