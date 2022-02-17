//
// Created by arkady on 16.02.2022.
//

#ifndef BASEBUSES_GETMAP_H
#define BASEBUSES_GETMAP_H

#include "StateListen.h"

namespace Requests {

    class GetMap : public StateListen {
    public:
        Json::Node Listen(BaseBuses &, const std::map<std::string, Json::Node> &) override;
    };

}
#endif //BASEBUSES_GETMAP_H
