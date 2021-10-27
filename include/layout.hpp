#pragma once

#define LAYOUT(l00, l01, l02, l03, l04, l05, r05, r04, r03, r02, r01, r00,     \
               l10, l11, l12, l13, l14, l15, r15, r14, r13, r12, r11, r10,     \
                    l21, l22, l23, l24, l25, r25, r24, r23, r22, r21,          \
                         l32, l33, l34, l35, r35, r34, r33, r32)               \
  {                                                                            \
    {                                                                          \
        l05, l04, l03, l02, l01, l00,                                          \
    },                                                                         \
    {                                                                          \
        l15, l14, l13, l12, l11, l10,                                          \
    },                                                                         \
    {                                                                          \
        l25, l24, l23, l22, l21, KC_XXXX,                                      \
    },                                                                         \
    {                                                                          \
        l35, l34, l33, l32, KC_XXXX, KC_XXXX,                                  \
    },                                                                         \
    {                                                                          \
        r05, r04, r03, r02, r01, r00,                                          \
    },                                                                         \
    {                                                                          \
        r15, r14, r13, r12, r11, r10,                                          \
    },                                                                         \
    {                                                                          \
        r25, r24, r23, r22, r21, KC_XXXX,                                      \
    },                                                                         \
    {                                                                          \
        r35, r34, r33, r32, KC_XXXX, KC_XXXX,                                  \
    },                                                                         \
  }

#define LAYOUT_kc( \
  L00, L01, L02, L03, L04, L05,    R00, R01, R02, R03, R04, R05, \
  L10, L11, L12, L13, L14, L15,    R10, R11, R12, R13, R14, R15, \
       L21, L22, L23, L24, L25,    R20, R21, R22, R23, R24,      \
            L30, L31, L32, L33,    R30, R31, R32, R33 \
  ) \
  LAYOUT( \
    KC_##L00, KC_##L01, KC_##L02, KC_##L03, KC_##L04, KC_##L05,     KC_##R00, KC_##R01, KC_##R02, KC_##R03, KC_##R04, KC_##R05, \
    KC_##L10, KC_##L11, KC_##L12, KC_##L13, KC_##L14, KC_##L15,     KC_##R10, KC_##R11, KC_##R12, KC_##R13, KC_##R14, KC_##R15, \
              KC_##L21, KC_##L22, KC_##L23, KC_##L24, KC_##L25,     KC_##R20, KC_##R21, KC_##R22, KC_##R23, KC_##R24, \
                        KC_##L30, KC_##L31, KC_##L32, KC_##L33,     KC_##R30, KC_##R31, KC_##R32, KC_##R33 \
  )
