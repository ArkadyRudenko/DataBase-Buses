#include "StateListen.h"

namespace StateListening {

    class GetBusInfo : public StateListen {
    public:
        void Listen(BaseBuses &buses, std::ostream &ostream, std::istream &istream) override;
    };

}