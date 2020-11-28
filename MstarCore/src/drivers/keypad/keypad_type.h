
#define bool                            MS_U8
#define MAXKEYPADCH       4 //Maximun supported keypad channels

#define KEYPADCH1 0
#define KEYPADCH2 1
#define KEYPADCH3 2
#define KEYPADCH4 3

///////////////////////////////////////////////////////////////////////////////
// Keypad SAR Info.
///////////////////////////////////////////////////////////////////////////////
/// define SAR Kpd Bounds

typedef struct
{
    ///upper bound
    unsigned char u8UpBnd;
    ///low bound
    unsigned char u8LoBnd;
} SAR_KpdBndCfg_t;

/// define SAR Kpd Configuration
typedef struct
{
    bool bEnable;
    unsigned char u8SARChID;
    SAR_KpdBndCfg_t tSARChBnd;
    unsigned char u8KeyLevelNum;  // 0-8 levels
    unsigned char u8KeyThreshold[8];  // each threshold match to one keycode
    unsigned char u8KeyCode[8];
} SAR_KpdRegCfg_t;

