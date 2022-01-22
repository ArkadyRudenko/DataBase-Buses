#include "StateListen.h"

namespace StateListening {

    class GetStopInfo : public StateListen {
    public:
        nlohmann::json Listen(BaseBuses&, const nlohmann::json&, std::ostream&) override;
    };
}