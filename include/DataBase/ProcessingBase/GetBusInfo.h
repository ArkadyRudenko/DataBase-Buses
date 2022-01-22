#include "StateListen.h"

namespace StateListening {

    class GetBusInfo : public StateListen {
    public:
        nlohmann::json Listen(BaseBuses&, const nlohmann::json&, std::ostream&) override;
    };

}