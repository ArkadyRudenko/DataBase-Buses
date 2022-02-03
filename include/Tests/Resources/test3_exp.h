//
// Created by arkady on 03.02.2022.
//

#ifndef BASEBUSES_TEST3_EXP_H
#define BASEBUSES_TEST3_EXP_H

stringstream LoadTest3Exp() {
    std::stringstream ss;
    ss << R"([
{ "curvature": 1.63414,"request_id": 1,"route_length": 24490,"stop_count": 7,"unique_stop_count": 4},
{ "items": [{ "stop_name": "Zagorye","time": 2,"type": "Wait"},{ "bus": "289","span_count": 1,"time": 0.46,"type": "Bus"},{ "stop_name": "Lipetskaya ulitsa 46","time": 2,"type": "Wait"},{ "bus": "289","span_count": 1,"time": 24.8,"type": "Bus"}],"request_id": 2,"total_time": 29.26},
{ "items": [{ "stop_name": "Moskvorechye","time": 2,"type": "Wait"},{ "bus": "289","span_count": 1,"time": 20,"type": "Bus"}],"request_id": 3,"total_time": 22},
{ "items": [],"request_id": 4,"total_time": 0}
])";
    return ss;
}

#endif //BASEBUSES_TEST3_EXP_H
