#include "StateListen.h"
#include "json.h"

namespace StateListening {

    class GetBusInfo : public StateListen {
    public:
        void Listen(BaseBuses&, const std::map<std::string, Json::Node>&, std::ostream&) override;
    };

}