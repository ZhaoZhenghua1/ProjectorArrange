#include "NameMap.h"
#include <QHash>

static QHash<QString, QString> names;
static QHash<QString, QString> values;

static inline void insert(const char *name, const char *value)
{
    names.insert(value, name);
    values.insert(name, value);
}

struct Global {
    Global();
};

Global::Global()
{
    insert("H264/AVC", "libx264");
    insert("H264/AVC (Hardware)", "h264_nvenc");
    insert("H265/HEVC", "libx265");
    insert("H265/HEVC (Hardware)", "hevc_nvenc");
    
    insert("YUV420", "yuv420p");
    insert("YUV422", "yuv422p");
    insert("YUV444", "yuv444p");

    insert("Ultrafast", "ultrafast");
    insert("Superfast", "superfast");
    insert("Veryfast", "veryfast");
    insert("Faster", "faster");
    insert("Fast", "fast");
    insert("Medium", "medium");
    insert("Slow", "slow");
    insert("Slower", "slower");
    insert("Veryslow", "veryslow");
    insert("Placebo", "placebo");
}

static Global g;

const QString &mapName(const QString &value)
{ return names.find(value).value(); }

const QString &mapValue(const QString &name)
{ return values.find(name).value(); }
