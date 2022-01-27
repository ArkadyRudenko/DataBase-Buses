#include "StateListen.h"

namespace StateListening {

    class GetStopInfo : public StateListen {
    public:
        void Listen(BaseBuses&, const std::map<std::string, Json::Node>&, std::ostream&) override;
    };
}