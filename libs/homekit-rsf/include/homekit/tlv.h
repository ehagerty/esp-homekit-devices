#ifndef __TLV_H__
#define __TLV_H__

#define TLVType_Method              (0x00)
#define TLVType_Identifier          (0x01)
#define TLVType_Salt                (0x02)
#define TLVType_PublicKey           (0x03)
#define TLVType_Proof               (0x04)
#define TLVType_EncryptedData       (0x05)
#define TLVType_State               (0x06)
#define TLVType_Error               (0x07)
#define TLVType_RetryDelay          (0x08)
#define TLVType_Certificate         (0x09)
#define TLVType_Signature           (0x0A)
#define TLVType_Permissions         (0x0B)
#define TLVType_FragmentData        (0x0C)
#define TLVType_FragmentLast        (0x0D)
#define TLVType_Flags               (0x13)
#define TLVType_Separator           (0xFF)

#define TLVMethod_PairSetup         (1)
#define TLVMethod_PairVerify        (2)
#define TLVMethod_AddPairing        (3)
#define TLVMethod_RemovePairing     (4)
#define TLVMethod_ListPairings      (5)

typedef unsigned char byte;

typedef struct _tlv {
    struct _tlv *next;
    byte type;
    byte *value;
    size_t size;
} tlv_t;


typedef struct {
    tlv_t *head;
} tlv_values_t;


tlv_values_t *tlv_new();

void tlv_free(tlv_values_t *values);

int tlv_add_value(tlv_values_t *values, byte type, const byte *value, size_t size);
int tlv_add_string_value(tlv_values_t *values, byte type, const char *value);
int tlv_add_integer_value(tlv_values_t *values, byte type, size_t size, int value);
int tlv_add_tlv_value(tlv_values_t *values, byte type, tlv_values_t *value);

tlv_t *tlv_get_value(const tlv_values_t *values, byte type);
int tlv_get_integer_value(const tlv_values_t *values, byte type, int def);
tlv_values_t *tlv_get_tlv_value(const tlv_values_t *values, byte type);

int tlv_format(const tlv_values_t *values, byte *buffer, size_t *size);

int tlv_parse(const byte *buffer, size_t length, tlv_values_t *values);

#endif // __TLV_H__
