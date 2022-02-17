#include "StateListen.h"

namespace Requests {

    class GetStopInfo : public StateListen {
    public:
        Json::Node Listen(BaseBuses&, const std::map<std::string, Json::Node>&) override;
    };
}