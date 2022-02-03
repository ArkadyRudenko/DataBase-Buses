//
// Created by arkady on 03.02.2022.
//

#ifndef BASEBUSES_TEST2_EXP_H
#define BASEBUSES_TEST2_EXP_H

stringstream LoadTest2Exp() {
    std::stringstream ss;
    ss << R"([
{ "curvature": 1.36159,"request_id": 1,"route_length": 5880,"stop_count": 6,"unique_stop_count": 5},
{ "curvature": 1.12195,"request_id": 2,"route_length": 14810,"stop_count": 11,"unique_stop_count": 6},
{ "curvature": 1.31245,"request_id": 3,"route_length": 15790,"stop_count": 11,"unique_stop_count": 6},
{ "buses": ["297","635","828"],"request_id": 4},
{ "items": [{ "stop_name": "Biryulyovo Zapadnoye","time": 2,"type": "Wait"},{ "bus": "828","span_count": 2,"time": 3,"type": "Bus"},{ "stop_name": "Biryusinka","time": 2,"type": "Wait"},{ "bus": "297","span_count": 1,"time": 0.42,"type": "Bus"}],"request_id": 5,"total_time": 7.42},
{ "items": [{ "stop_name": "Biryulyovo Zapadnoye","time": 2,"type": "Wait"},{ "bus": "828","span_count": 4,"time": 9.44,"type": "Bus"}],"request_id": 6,"total_time": 11.44},
{ "items": [{ "stop_name": "Biryulyovo Tovarnaya","time": 2,"type": "Wait"},{ "bus": "297","span_count": 1,"time": 1.78,"type": "Bus"},{ "stop_name": "Universam","time": 2,"type": "Wait"},{ "bus": "828","span_count": 1,"time": 4.92,"type": "Bus"}],"request_id": 7,"total_time": 10.7},
{ "items": [{ "stop_name": "Biryulyovo Tovarnaya","time": 2,"type": "Wait"},{ "bus": "297","span_count": 4,"time": 6.56,"type": "Bus"}],"request_id": 8,"total_time": 8.56},
{ "items": [{ "stop_name": "Biryulyovo Tovarnaya","time": 2,"type": "Wait"},{ "bus": "635","span_count": 5,"time": 14.32,"type": "Bus"}],"request_id": 9,"total_time": 16.32},
{ "items": [{ "stop_name": "Apteka","time": 2,"type": "Wait"},{ "bus": "297","span_count": 1,"time": 2.84,"type": "Bus"},{ "stop_name": "Biryulyovo Zapadnoye","time": 2,"type": "Wait"},{ "bus": "297","span_count": 1,"time": 5.2,"type": "Bus"}],"request_id": 10,"total_time": 12.04},
{ "error_message": "not found","request_id": 11}
])";
    return ss;
}

#endif //BASEBUSES_TEST2_EXP_H
