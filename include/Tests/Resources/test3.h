//
// Created by arkady on 02.02.2022.
//

#ifndef BASEBUSES_TEST3_H
#define BASEBUSES_TEST3_H

#include <sstream>

stringstream LoadTest3() {
    std::stringstream ss;
    ss << R"({
  "routing_settings": {
    "bus_wait_time": 2,
    "bus_velocity": 30
  },
"render_settings": {
        "width": 1200,
        "height": 1200,
        "padding": 50,
        "stop_radius": 5,
        "line_width": 14,
        "bus_label_font_size": 20,
        "bus_label_offset": [
            7,
            15
        ],
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
        ],
        "layers": [
            "bus_lines",
            "stop_points",
            "bus_labels"
        ]
    },
  "base_requests": [
    {
      "type": "Bus",
      "name": "289",
      "stops": [
        "Zagorye",
        "Lipetskaya ulitsa 46",
        "Lipetskaya ulitsa 40",
        "Lipetskaya ulitsa 40",
        "Lipetskaya ulitsa 46",
        "Moskvorechye",
        "Zagorye"
      ],
      "is_roundtrip": true
    },
    {
      "type": "Stop",
      "road_distances": {
        "Lipetskaya ulitsa 46": 230
      },
      "longitude": 37.68372,
      "name": "Zagorye",
      "latitude": 55.579909
    },
    {
      "type": "Stop",
      "road_distances": {
        "Lipetskaya ulitsa 40": 390,
        "Moskvorechye": 12400
      },
      "longitude": 37.682205,
      "name": "Lipetskaya ulitsa 46",
      "latitude": 55.581441
    },
    {
      "type": "Stop",
      "road_distances": {
        "Lipetskaya ulitsa 40": 1090,
        "Lipetskaya ulitsa 46": 380
      },
      "longitude": 37.679133,
      "name": "Lipetskaya ulitsa 40",
      "latitude": 55.584496
    },
    {
      "type": "Stop",
      "road_distances": {
        "Zagorye": 10000
      },
      "longitude": 37.638433,
      "name": "Moskvorechye",
      "latitude": 55.638433
    }
  ],
  "stat_requests": [
    {
      "type": "Bus",
      "name": "289",
      "id": 1
    },
    {
      "type": "Route",
      "from": "Zagorye",
      "to": "Moskvorechye",
      "id": 2
    },
    {
      "type": "Route",
      "from": "Moskvorechye",
      "to": "Zagorye",
      "id": 3
    },
    {
      "type": "Route",
      "from": "Lipetskaya ulitsa 40",
      "to": "Lipetskaya ulitsa 40",
      "id": 4
    }
  ]
})";
    return ss;
}

#endif //BASEBUSES_TEST3_H
