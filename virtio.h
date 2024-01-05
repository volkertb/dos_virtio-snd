//
// Created by volkert on 1/4/24.
//

#ifndef VIRTIO_H
#define VIRTIO_H

/**
 * 5.14.4 Device Configuration Layout
 * https://docs.oasis-open.org/virtio/virtio/v1.3/csd01/virtio-v1.3-csd01.html#x1-5710004
 */
struct virtio_snd_config {
    le32 jacks;
    le32 streams;
    le32 chmaps;
    le32 controls;
};

/**
 * 5.14.6 Device Operation
 */
enum {
    /* jack control request types */
    VIRTIO_SND_R_JACK_INFO = 1,
    VIRTIO_SND_R_JACK_REMAP,

    /* PCM control request types */
    VIRTIO_SND_R_PCM_INFO = 0x0100,
    VIRTIO_SND_R_PCM_SET_PARAMS,
    VIRTIO_SND_R_PCM_PREPARE,
    VIRTIO_SND_R_PCM_RELEASE,
    VIRTIO_SND_R_PCM_START,
    VIRTIO_SND_R_PCM_STOP,

    /* channel map control request types */
    VIRTIO_SND_R_CHMAP_INFO = 0x0200,

    /* control element request types */
    VIRTIO_SND_R_CTL_INFO = 0x0300,
    VIRTIO_SND_R_CTL_ENUM_ITEMS,
    VIRTIO_SND_R_CTL_READ,
    VIRTIO_SND_R_CTL_WRITE,
    VIRTIO_SND_R_CTL_TLV_READ,
    VIRTIO_SND_R_CTL_TLV_WRITE,
    VIRTIO_SND_R_CTL_TLV_COMMAND,

    /* jack event types */
    VIRTIO_SND_EVT_JACK_CONNECTED = 0x1000,
    VIRTIO_SND_EVT_JACK_DISCONNECTED,

    /* PCM event types */
    VIRTIO_SND_EVT_PCM_PERIOD_ELAPSED = 0x1100,
    VIRTIO_SND_EVT_PCM_XRUN,

    /* control element event types */
    VIRTIO_SND_EVT_CTL_NOTIFY = 0x1200,

    /* common status codes */
    VIRTIO_SND_S_OK = 0x8000,
    VIRTIO_SND_S_BAD_MSG,
    VIRTIO_SND_S_NOT_SUPP,
    VIRTIO_SND_S_IO_ERR
};

/* a common header */
struct virtio_snd_hdr {
    le32 code;
};

/* an event notification */
struct virtio_snd_event {
    struct virtio_snd_hdr hdr;
    le32 data;
};

enum {
    VIRTIO_SND_D_OUTPUT = 0,
    VIRTIO_SND_D_INPUT
};

/**
 * 5.14.6.1 Item Information Request
 */
struct virtio_snd_query_info {
    struct virtio_snd_hdr hdr;
    le32 start_id;
    le32 count;
    le32 size;
};

struct virtio_snd_info {
    le32 hda_fn_nid;
};

/**
 * 5.14.6.4 Jack Control Messages
 */
struct virtio_snd_jack_hdr {
    struct virtio_snd_hdr hdr;
    le32 jack_id;
};

/**
 * 5.14.6.4.1 VIRTIO_SND_R_JACK_INFO
 */
/* supported jack features */
enum {
    VIRTIO_SND_JACK_F_REMAP = 0
};

struct virtio_snd_jack_info {
    struct virtio_snd_info hdr;
    le32 features; /* 1 << VIRTIO_SND_JACK_F_XXX */
    le32 hda_reg_defconf;
    le32 hda_reg_caps;
    u8 connected;

    u8 padding[7];
};

/**
 * 5.14.6.4.2 VIRTIO_SND_R_JACK_REMAP
 */
struct virtio_snd_jack_remap {
    struct virtio_snd_jack_hdr hdr; /* .code = VIRTIO_SND_R_JACK_REMAP */
    le32 association;
    le32 sequence;
};

/**
 * 5.14.6.6 PCM Control Messages
 */
struct virtio_snd_pcm_hdr {
    struct virtio_snd_hdr hdr;
    le32 stream_id;
};

/*
 * 5.14.6.6.2 VIRTIO_SND_R_PCM_INFO
 */

/* supported PCM stream features */
enum {
    VIRTIO_SND_PCM_F_SHMEM_HOST = 0,
    VIRTIO_SND_PCM_F_SHMEM_GUEST,
    VIRTIO_SND_PCM_F_MSG_POLLING,
    VIRTIO_SND_PCM_F_EVT_SHMEM_PERIODS,
    VIRTIO_SND_PCM_F_EVT_XRUNS
};

/* supported PCM sample formats */
enum {
    /* analog formats (width / physical width) */
    VIRTIO_SND_PCM_FMT_IMA_ADPCM = 0,   /*  4 /  4 bits */
    VIRTIO_SND_PCM_FMT_MU_LAW,          /*  8 /  8 bits */
    VIRTIO_SND_PCM_FMT_A_LAW,           /*  8 /  8 bits */
    VIRTIO_SND_PCM_FMT_S8,              /*  8 /  8 bits */
    VIRTIO_SND_PCM_FMT_U8,              /*  8 /  8 bits */
    VIRTIO_SND_PCM_FMT_S16,             /* 16 / 16 bits */
    VIRTIO_SND_PCM_FMT_U16,             /* 16 / 16 bits */
    VIRTIO_SND_PCM_FMT_S18_3,           /* 18 / 24 bits */
    VIRTIO_SND_PCM_FMT_U18_3,           /* 18 / 24 bits */
    VIRTIO_SND_PCM_FMT_S20_3,           /* 20 / 24 bits */
    VIRTIO_SND_PCM_FMT_U20_3,           /* 20 / 24 bits */
    VIRTIO_SND_PCM_FMT_S24_3,           /* 24 / 24 bits */
    VIRTIO_SND_PCM_FMT_U24_3,           /* 24 / 24 bits */
    VIRTIO_SND_PCM_FMT_S20,             /* 20 / 32 bits */
    VIRTIO_SND_PCM_FMT_U20,             /* 20 / 32 bits */
    VIRTIO_SND_PCM_FMT_S24,             /* 24 / 32 bits */
    VIRTIO_SND_PCM_FMT_U24,             /* 24 / 32 bits */
    VIRTIO_SND_PCM_FMT_S32,             /* 32 / 32 bits */
    VIRTIO_SND_PCM_FMT_U32,             /* 32 / 32 bits */
    VIRTIO_SND_PCM_FMT_FLOAT,           /* 32 / 32 bits */
    VIRTIO_SND_PCM_FMT_FLOAT64,         /* 64 / 64 bits */
    /* digital formats (width / physical width) */
    VIRTIO_SND_PCM_FMT_DSD_U8,          /*  8 /  8 bits */
    VIRTIO_SND_PCM_FMT_DSD_U16,         /* 16 / 16 bits */
    VIRTIO_SND_PCM_FMT_DSD_U32,         /* 32 / 32 bits */
    VIRTIO_SND_PCM_FMT_IEC958_SUBFRAME  /* 32 / 32 bits */
};

/* supported PCM frame rates */
enum {
    VIRTIO_SND_PCM_RATE_5512 = 0,
    VIRTIO_SND_PCM_RATE_8000,
    VIRTIO_SND_PCM_RATE_11025,
    VIRTIO_SND_PCM_RATE_16000,
    VIRTIO_SND_PCM_RATE_22050,
    VIRTIO_SND_PCM_RATE_32000,
    VIRTIO_SND_PCM_RATE_44100,
    VIRTIO_SND_PCM_RATE_48000,
    VIRTIO_SND_PCM_RATE_64000,
    VIRTIO_SND_PCM_RATE_88200,
    VIRTIO_SND_PCM_RATE_96000,
    VIRTIO_SND_PCM_RATE_176400,
    VIRTIO_SND_PCM_RATE_192000,
    VIRTIO_SND_PCM_RATE_384000
};

struct virtio_snd_pcm_info {
    struct virtio_snd_info hdr;
    le32 features; /* 1 << VIRTIO_SND_PCM_F_XXX */
    le64 formats; /* 1 << VIRTIO_SND_PCM_FMT_XXX */
    le64 rates; /* 1 << VIRTIO_SND_PCM_RATE_XXX */
    u8 direction;
    u8 channels_min;
    u8 channels_max;

    u8 padding[5];
};

/**
 * 5.14.6.6.3 VIRTIO_SND_R_PCM_SET_PARAMS
 */
struct virtio_snd_pcm_set_params {
    struct virtio_snd_pcm_hdr hdr; /* .code = VIRTIO_SND_R_PCM_SET_PARAMS */
    le32 buffer_bytes;
    le32 period_bytes;
    le32 features; /* 1 << VIRTIO_SND_PCM_F_XXX */
    u8 channels;
    u8 format;
    u8 rate;

    u8 padding;
};

/*
 * 5.14.6.8 PCM I/O Messages
 */

/* an I/O header */
struct virtio_snd_pcm_xfer {
    le32 stream_id;
};

/* an I/O status */
struct virtio_snd_pcm_status {
    le32 status;
    le32 latency_bytes;
};

/*
 * 5.14.6.9.1 VIRTIO_SND_R_CHMAP_INFO
 */

/* standard channel position definition */
enum {
    VIRTIO_SND_CHMAP_NONE = 0,  /* undefined */
    VIRTIO_SND_CHMAP_NA,        /* silent */
    VIRTIO_SND_CHMAP_MONO,      /* mono stream */
    VIRTIO_SND_CHMAP_FL,        /* front left */
    VIRTIO_SND_CHMAP_FR,        /* front right */
    VIRTIO_SND_CHMAP_RL,        /* rear left */
    VIRTIO_SND_CHMAP_RR,        /* rear right */
    VIRTIO_SND_CHMAP_FC,        /* front center */
    VIRTIO_SND_CHMAP_LFE,       /* low frequency (LFE) */
    VIRTIO_SND_CHMAP_SL,        /* side left */
    VIRTIO_SND_CHMAP_SR,        /* side right */
    VIRTIO_SND_CHMAP_RC,        /* rear center */
    VIRTIO_SND_CHMAP_FLC,       /* front left center */
    VIRTIO_SND_CHMAP_FRC,       /* front right center */
    VIRTIO_SND_CHMAP_RLC,       /* rear left center */
    VIRTIO_SND_CHMAP_RRC,       /* rear right center */
    VIRTIO_SND_CHMAP_FLW,       /* front left wide */
    VIRTIO_SND_CHMAP_FRW,       /* front right wide */
    VIRTIO_SND_CHMAP_FLH,       /* front left high */
    VIRTIO_SND_CHMAP_FCH,       /* front center high */
    VIRTIO_SND_CHMAP_FRH,       /* front right high */
    VIRTIO_SND_CHMAP_TC,        /* top center */
    VIRTIO_SND_CHMAP_TFL,       /* top front left */
    VIRTIO_SND_CHMAP_TFR,       /* top front right */
    VIRTIO_SND_CHMAP_TFC,       /* top front center */
    VIRTIO_SND_CHMAP_TRL,       /* top rear left */
    VIRTIO_SND_CHMAP_TRR,       /* top rear right */
    VIRTIO_SND_CHMAP_TRC,       /* top rear center */
    VIRTIO_SND_CHMAP_TFLC,      /* top front left center */
    VIRTIO_SND_CHMAP_TFRC,      /* top front right center */
    VIRTIO_SND_CHMAP_TSL,       /* top side left */
    VIRTIO_SND_CHMAP_TSR,       /* top side right */
    VIRTIO_SND_CHMAP_LLFE,      /* left LFE */
    VIRTIO_SND_CHMAP_RLFE,      /* right LFE */
    VIRTIO_SND_CHMAP_BC,        /* bottom center */
    VIRTIO_SND_CHMAP_BLC,       /* bottom left center */
    VIRTIO_SND_CHMAP_BRC        /* bottom right center */
};

/* maximum possible number of channels */
#define VIRTIO_SND_CHMAP_MAX_SIZE 18

struct virtio_snd_chmap_info {
    struct virtio_snd_info hdr;
    u8 direction;
    u8 channels;
    u8 positions[VIRTIO_SND_CHMAP_MAX_SIZE];
};

/**
 * 5.14.6.10 Control Elements
 */
struct virtio_snd_ctl_hdr {
    struct virtio_snd_hdr hdr;
    le32 control_id;
};

/*
 * 5.14.6.10.1 Query information
 */

enum {
    VIRTIO_SND_CTL_ROLE_UNDEFINED = 0,
    VIRTIO_SND_CTL_ROLE_VOLUME,
    VIRTIO_SND_CTL_ROLE_MUTE,
    VIRTIO_SND_CTL_ROLE_GAIN
};

enum {
    VIRTIO_SND_CTL_TYPE_BOOLEAN = 0,
    VIRTIO_SND_CTL_TYPE_INTEGER,
    VIRTIO_SND_CTL_TYPE_INTEGER64,
    VIRTIO_SND_CTL_TYPE_ENUMERATED,
    VIRTIO_SND_CTL_TYPE_BYTES,
    VIRTIO_SND_CTL_TYPE_IEC958
};

enum {
    VIRTIO_SND_CTL_ACCESS_READ = 0,
    VIRTIO_SND_CTL_ACCESS_WRITE,
    VIRTIO_SND_CTL_ACCESS_VOLATILE,
    VIRTIO_SND_CTL_ACCESS_INACTIVE,
    VIRTIO_SND_CTL_ACCESS_TLV_READ,
    VIRTIO_SND_CTL_ACCESS_TLV_WRITE,
    VIRTIO_SND_CTL_ACCESS_TLV_COMMAND
};

struct virtio_snd_ctl_info {
    struct virtio_snd_info hdr;
    le32 role;
    le32 type;
    le32 access; /* 1 << VIRTIO_SND_CTL_ACCESS_XXX */
    le32 count;
    le32 index;
    u8 name[44];
    union {
        struct {
            le32 min;
            le32 max;
            le32 step;
        } integer;
        struct {
            le64 min;
            le64 max;
            le64 step;
        } integer64;
        struct {
            le32 items;
        } enumerated;
    } value;
};

struct virtio_snd_ctl_enum_item {
    u8 item[64];
};

/*
 * 5.14.6.10.2 Value
 */

struct virtio_snd_ctl_iec958 {
    u8 status[24];      /* AES/IEC958 channel status bits */
    u8 subcode[147];    /* AES/IEC958 subcode bits */
    u8 pad;             /* nothing */
    u8 dig_subframe[4]; /* AES/IEC958 subframe bits */
};

struct virtio_snd_ctl_value {
    union {
        le32 integer[128];
        le64 integer64[64];
        le32 enumerated[128];
        u8 bytes[512];
        struct virtio_snd_ctl_iec958 iec958;
    } value;
};

/**
 * 5.14.6.10.3 Metadata
 */
struct virtio_snd_ctl_tlv {
    le32 type;
    le32 length;
    le32 value[];
};

/*
 * 5.14.6.10.4 Notifications
 */
enum {
    VIRTIO_SND_CTL_EVT_MASK_VALUE = 0,
    VIRTIO_SND_CTL_EVT_MASK_INFO,
    VIRTIO_SND_CTL_EVT_MASK_TLV
};

struct virtio_snd_ctl_event {
    struct virtio_snd_hdr hdr; /* .code = VIRTIO_SND_EVT_CTL_NOTIFY */
    le16 control_id;
    le16 mask; /* 1 << VIRTIO_SND_CTL_EVT_MASK_XXX */
};

#endif //VIRTIO_H
