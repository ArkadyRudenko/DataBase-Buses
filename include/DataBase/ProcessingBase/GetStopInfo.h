#include "StateListen.h"

namespace StateListening {

    class GetStopInfo : public StateListen {
    public:
        void Listen(BaseBuses &buses, std::ostream &os, std::istream &is) override;
    };
}