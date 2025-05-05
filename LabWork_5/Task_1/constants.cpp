#include "constants.h"
#include <QVector>

const QString Keyboards[8][2] = {
    // English (0)
    {
        "`1234567890-=qwertyuiop[]\\asdfghjkl;'zxcvbnm,./",
        "~!@#$%^?*()_+QWERTYUIOP{}|ASDFGHJKL:\"ZXCVBNM<>?"
    },
    // Russian (1)
    {
        "`1234567890-=йцукенгшщзхъ\\фывапролджэячсмитьбю.",
        "~!@#$%^?*()_+ЙЦУКЕНГШЩЗХЪ|ФЫВАПРОЛДЖЭЯЧСМИТЬБЮ,"
    },
    // German (2)
    {
        "`1234567890-=qwertzuiopü+\\asdfghjklöäyxcvbnm,./",
        "~!@#$%^?*()_+QWERTZUIOPÜ*|ASDFGHJKLÖÄYXCVBNM<>?"
    },
    // French (3)
    {
        "`1234567890-=azertyuiop^$\\qsdfghjklmùwxcvbn,;./",
        "~!@#$%^?*()_+AZERTYUIOP{}|QSDFGHJKLMÙWXCVBNM<>?"
    },
    // Arabic (4)
    {
        "`1234567890-=ضصثقفغعهخحجد\\شسيبلاتنمكطئءرزظد,;./",
        "~!@#$%^?*()_+ضصثفغعهخحجد|شسيبلاتنمكطئءرزظدىة<>?"
    },
    // Chinese (5)
    {
        "`1234567890-=手田水口廿卜山戈人心[]\\日尸木火土竹十大中;'Ｚ難金女月弓一,./",
        "~!@#$%^?*()_+手田水口廿卜山戈人心{}|日尸木火土竹十大中:\"Ｚ難金女月弓一<>?"
    },
    // Belarusian (6)
    {
        "`1234567890-=йцукенгшўзх'\\фывапролджэячсмитьбю.",
        "~!@#$%^?*()_+ЙЦУКЕНГШЎЗХ\"|ФЫВАПРОЛДЖЭЯЧСМИТЬБЮ,"
    },
    // Hebrew (7)
    {
        "`1234567890-=קראטוןםפ][\\שדגכעיחלךף,זסבהנמצתץ,./",
        "~!@#$%^?*()_+קראטוןםפ{}|שדגכעיחלךף:זסבהנמצתץ<>?"
    }
};

const QString ExampleTexts[8] = {
    // English (0)
    "In a quiet village, nestled by a winding river, the sun rises slowly, casting golden rays over lush green hills. Birds, perched on ancient trees, sing melodious tunes, while a soft breeze carries the scent of wildflowers. On a warm porch, a cat lounges lazily, watching villagers, who stroll along a dusty path, admiring the starry sky that blankets the serene night.",
    // Russian (1)
    "В тихой деревне, расположенной у извилистой реки, солнце медленно встаёт, озаряя золотыми лучами зелёные холмы. Птицы, сидящие на старых деревьях, поют звонкие мелодии, а лёгкий ветерок несёт аромат полевых цветов. На тёплом крыльце кот лениво нежится, наблюдая за жителями, которые неспешно идут по пыльной тропе, любуясь звёздным небом, укрывающим ночь.",
    // German (2)
    "In einem stillen Dorf, das an einem gewundenen Fluss liegt, geht die Sonne langsam auf, wirft goldene Strahlen über grüne Hügel. Vögel, die auf alten Bäumen sitzen, singen klare Melodien, während eine sanfte Brise den Duft von Wildblumen trägt. Auf einer warmen Veranda ruht eine Katze träge, blickt auf Dorfbewohner, die einen staubigen Pfad entlanggehen, das funkelnde Sternenhimmel betrachtend.",
    // French (3)
    "Dans un village paisible, blotti près d’une rivière sinueuse, le soleil se lève doucement, projetant des rayons dorés sur les collines verdoyantes. Les oiseaux, perchés sur de vieux arbres, chantent des mélodies claires, tandis qu’une brise légère porte le parfum des fleurs sauvages. Sur un porche chaud, un chat se repose paresseusement, observant les villageois, qui marchent sur un chemin poussiéreux, admirant le ciel étoilé.",
    // Arabic (4)
    "في قرية هادئة، تقع بجانب نهر متعرج، تشرق الشمس ببطء، ملقية أشعة ذهبية على التلال الخضراء. الطيور، الجاثمة على أشجار قديمة، تغني ألحانًا نقية، بينما نسيم خفيف يحمل رائحة الزهور البرية. على شرفة دافئة، قطة تستريح بكسل، تراقب القرويين، الذين يسيرون على درب مغبر، معجبين بالسماء المرصعة بالنجوم.",
    // Chinese (5)
    "在一个宁静的村庄，依偎在蜿蜒的河边，太阳缓缓升起，洒下金色光芒覆盖绿色山丘。鸟儿，栖息在古老的树上，唱着清脆的旋律，而微风带来了野花的芬芳。在温暖的门廊上，一只猫懒洋洋地休息，注视着村民，他们沿着尘土小路漫步，欣赏覆盖夜晚的璀璨星空。",
    // Belarusian (6)
    "У ціхай вёсцы, што стаіць каля звілістай ракі, сонца павольна ўзыходзіць, рассыпаючы залатыя промні па зялёных пагорках. Птушкі, якія сядзяць на старых дрэвах, спяваюць чыстыя мелодыі, а лёгкі вецер нясе водар палявых кветак. На цёплым ганку кот лянуецца, пазіраючы на вяскоўцаў, якія ідуць па пылістай сцежцы, захапляючыся зорным небам, што ахінае ноч.",
    // Hebrew (7)
    "בכפר שקט, השוכן ליד נהר מפותל, השמש זורחת לאט, מפזרת קרני זהב על גבעות ירוקות. ציפורים, היושבות על עצים עתיקים, שרות מנגינות צלולות, בעוד רוח קלה נושאת את ניחוח פרחי הבר. במרפסת חמה, חתול נח בעצלות, מביט בתושבים, ההולכים בשביל מאובק, מתפעלים משמי הכוכבים המכסים את הלילה."
};

QString getLanguageName(int index)
{
    return LanguageNames[index];
}
