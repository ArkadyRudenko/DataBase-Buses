//
// Created by arkady on 03.02.2022.
//

#ifndef BASEBUSES_TEST1_H
#define BASEBUSES_TEST1_H

stringstream LoadTest1() {
    std::stringstream ss;
    ss << R"({
  "routing_settings": {
    "bus_wait_time": 6,
    "bus_velocity": 40
  },
"render_settings": {
        "width": 1200,
        "height": 1200,
        "padding": 50,
        "stop_radius": 5,
        "line_width": 14,
        "stop_label_font_size": 20,
        "stop_label_offset": [
            7,
            -3
        ],
        "underlayer_color": [
            255,
            255,
            255,
            0.85
        ],
        "underlayer_width": 3,
        "color_palette": [
            "green",
            [
                255,
                160,
                0
            ],
            "red"
        ]
    },
  "base_requests": [
    {
      "type": "Bus",
      "name": "297",
      "stops": [
        "Biryulyovo Zapadnoye",
        "Biryulyovo Tovarnaya",
        "Universam",
        "Biryulyovo Zapadnoye"
      ],
      "is_roundtrip": true
    },
    {
      "type": "Bus",
      "name": "635",
      "stops": [
        "Biryulyovo Tovarnaya",
        "Universam",
        "Prazhskaya"
      ],
      "is_roundtrip": false
    },
    {
      "type": "Stop",
      "road_distances": {
        "Biryulyovo Tovarnaya": 2600
      },
      "longitude": 37.6517,
      "name": "Biryulyovo Zapadnoye",
      "latitude": 55.574371
    },
    {
      "type": "Stop",
      "road_distances": {
        "Prazhskaya": 4650,
        "Biryulyovo Tovarnaya": 1380,
        "Biryulyovo Zapadnoye": 2500
      },
      "longitude": 37.645687,
      "name": "Universam",
      "latitude": 55.587655
    },
    {
      "type": "Stop",
      "road_distances": {
        "Universam": 890
      },
      "longitude": 37.653656,
      "name": "Biryulyovo Tovarnaya",
      "latitude": 55.592028
    },
    {
      "type": "Stop",
      "road_distances": {},
      "longitude": 37.603938,
      "name": "Prazhskaya",
      "latitude": 55.611717
    }
  ],
  "stat_requests": [
    {
      "type": "Bus",
      "name": "297",
      "id": 1
    },
    {
      "type": "Bus",
      "name": "635",
      "id": 2
    },
    {
      "type": "Stop",
      "name": "Universam",
      "id": 3
    },
    {
      "type": "Route",
      "from": "Biryulyovo Zapadnoye",
      "to": "Universam",
      "id": 4
    },
    {
      "type": "Route",
      "from": "Biryulyovo Zapadnoye",
      "to": "Prazhskaya",
      "id": 5
    }
  ]
})";
    return ss;
}


#endif //BASEBUSES_TEST1_H
