#include <vector>
#include <eckit/testing/Test.h>

enum class PackingType {
    SIMPLE,
    CCSDS
};

class InputData {
public:
    PackingType packingType;
    std::string gribFileName;
    std::vector<double> expectedData;
    double epsilon = 1e-12;
    std::string expectedString;
};

constexpr double MISSING_VAL = std::numeric_limits<double>::quiet_NaN();
std::vector<InputData> testData;

void add_simple_no_bitmask() {
    // Grib with no bitmask
    testData.push_back(
        InputData{
            .packingType = PackingType::SIMPLE,
            .gribFileName = "no_mask.grib",
            .expectedData = {
                238.97477722168, 238.97477722168, 238.97477722168, 238.97477722168, 238.97477722168,
                238.97477722168, 238.97477722168, 238.97477722168, 238.97477722168, 238.97477722168,
                238.97477722168, 238.97477722168, 238.97477722168, 238.97477722168, 238.97477722168,
                238.97477722168, 238.97477722168, 238.97477722168, 238.97477722168, 238.97477722168,
                238.97477722168, 238.97477722168, 238.97477722168, 238.97477722168, 238.97477722168,
                238.97477722168, 238.97477722168, 238.97477722168, 238.97477722168, 238.97477722168,
                238.97477722168, 238.97477722168, 238.97477722168, 238.97477722168, 238.97477722168,
                238.97477722168, 241.45329284668, 241.45036315918, 241.18180847168, 240.62223815918,
                239.86051940918, 239.12809753418, 238.68766784668, 238.62907409668, 238.74919128418,
                238.66227722168, 238.09684753418, 237.11247253418, 236.05290222168, 235.28532409668,
                234.98063659668, 235.07731628418, 235.39665222168, 235.77458190918, 236.12126159668,
                236.44157409668, 236.82145690918, 237.37321472168, 238.14079284668, 239.02165222168,
                239.79411315918, 240.23063659668, 240.20426940918, 239.75212097168, 239.09489440918,
                238.58317565918, 238.50798034668, 238.92106628418, 239.61930847168, 240.32926940918,
                240.88493347168, 241.25602722168, 248.64665222168, 248.49919128418, 247.54997253418,
                245.71696472168, 243.26579284668, 241.02067565918, 240.20622253418, 241.48942565918,
                243.95719909668, 245.51188659668, 244.66423034668, 241.82145690918, 238.79899597168,
                237.28337097168, 237.66130065918, 239.06950378418, 240.42399597168, 241.25505065918,
                241.63102722168, 241.74137878418, 241.84294128418, 242.42887878418, 243.98649597168,
                246.39079284668, 248.85466003418, 250.56169128418, 250.95426940918, 249.55583190918,
                246.55583190918, 243.55387878418, 242.53923034668, 243.83024597168, 245.88591003418,
                247.26286315918, 247.88883972168, 248.31950378418, 253.16813659668, 252.60856628418,
                250.37223815918, 247.65544128418, 245.36051940918, 243.94548034668, 243.95622253418,
                246.13493347168, 249.71403503418, 251.97087097168, 251.04313659668, 247.46403503418,
                243.26091003418, 241.25700378418, 242.89079284668, 246.00309753418, 247.39372253418,
                246.61051940918, 245.59001159668, 245.85954284668, 246.88395690918, 247.37516784668,
                247.76188659668, 249.28141784668, 251.53825378418, 253.73844909668, 255.72477722168,
                255.49430847168, 250.78044128418, 244.56266784668, 242.78337097168, 246.05778503418,
                249.35856628418, 249.94450378418, 250.12907409668, 251.74626159668, 257.32536315918,
                255.13200378418, 251.94841003418, 249.39274597168, 249.38102722168, 252.07243347168,
                253.81169128418, 253.17497253418, 252.24821472168, 251.84684753418, 252.21598815918,
                252.11637878418, 248.48551940918, 244.67692565918, 247.10856628418, 252.84684753418,
                254.86344909668, 252.22380065918, 248.91520690918, 249.50309753418, 253.48747253418,
                254.68669128418, 251.30973815918, 248.87419128418, 249.63883972168, 251.18962097168,
                253.70329284668, 255.72184753418, 252.46891784668, 246.11149597168, 244.36540222168,
                248.00700378418, 250.42887878418, 249.78532409668, 251.40055847168, 255.74137878418,
                260.34489440918, 257.46012878418, 256.93864440918, 255.38981628418, 254.99137878418,
                258.46989440918, 259.77751159668, 256.41130065918, 254.23063659668, 254.98551940918,
                257.18278503418, 259.04704284668, 255.77751159668, 251.84294128418, 255.83024597168,
                261.90739440918, 263.54801940918, 262.34684753418, 259.29508972168, 257.75505065918,
                260.02458190918, 260.29411315918, 254.88200378418, 250.79020690918, 252.78141784668,
                255.42399597168, 256.74430847168, 258.68083190918, 258.78044128418, 256.00212097168,
                253.12809753418, 253.44743347168, 255.51676940918, 256.66618347168, 259.75798034668,
                262.61051940918, 261.28141784668, 260.52067565918, 261.52946472168, 260.05192565918,
                259.31462097168, 262.70329284668, 264.69938659668, 262.20817565918, 261.52067565918,
                264.42008972168, 265.73649597168, 265.53044128418, 263.92008972168, 262.96403503418,
                265.88591003418, 266.51969909668, 265.02751159668, 265.52555847168, 264.37223815918,
                262.08219909668, 261.42497253418, 261.35856628418, 260.01286315918, 258.43669128418,
                259.65446472168, 261.15153503418, 261.36930847168, 262.47282409668, 263.72380065918,
                263.13591003418, 259.58415222168, 258.83512878418, 262.59782409668, 264.37809753418,
                264.96598815918, 264.32731628418, 264.27067565918, 264.82731628418, 264.97575378418,
                264.49626159668, 265.05680847168, 268.09294128418, 271.08122253418, 269.89762878418,
                267.41716003418, 268.52360534668, 268.89469909668, 268.24723815918, 268.44450378418,
                267.84098815918, 267.93864440918, 267.25602722168, 266.82048034668, 267.32536315918,
                265.35466003418, 263.34587097168, 263.19255065918, 263.28630065918, 263.82829284668,
                264.79411315918, 265.37419128418, 264.99040222168, 265.31950378418, 266.72477722168,
                267.22087097168, 266.53532409668, 264.94938659668, 265.98747253418, 268.13688659668,
                267.00798034668, 265.39079284668, 264.48844909668, 267.04997253418, 266.98161315918,
                267.16032409668, 267.64079284668, 268.34196472168, 269.85758972168, 271.25700378418,
                270.30876159668, 268.87907409668, 269.56364440918, 269.57048034668, 269.32926940918,
                269.54118347168, 268.91813659668, 268.73942565918, 268.84489440918, 268.83317565918,
                269.13200378418, 268.24528503418, 266.16130065918, 265.96891784668, 266.70524597168,
                266.57536315918, 267.83415222168, 268.78923034668, 268.17594909668, 268.78337097168,
                269.50505065918, 269.67985534668, 268.96305847168, 267.97087097168, 269.24723815918,
                269.48454284668, 268.13981628418, 267.35954284668, 266.92301940918, 267.64860534668,
                268.05387878418, 268.62712097168, 268.09294128418, 268.44352722168, 268.92301940918,
                269.58415222168, 269.16520690918, 268.96696472168, 269.13786315918, 269.08512878418,
                269.62614440918, 269.35075378418, 269.48844909668, 269.33512878418, 268.95524597168,
                269.08512878418, 269.19743347168, 268.94743347168, 267.95915222168, 268.01383972168,
                268.57341003418, 268.30387878418, 268.93669128418, 269.30192565918, 269.33805847168,
                270.46598815918, 269.65934753418, 269.01774597168, 268.95915222168, 268.36540222168,
                269.04118347168, 269.24235534668, 268.95622253418, 268.65446472168, 268.37712097168,
                268.38981628418, 268.43083190918, 268.30192565918, 267.66032409668, 268.84880065918,
                267.67887878418, 268.07145690918, 269.29704284668, 269.27653503418, 269.06852722168,
                268.84391784668, 268.64762878418, 267.95817565918, 268.17008972168, 268.35954284668,
                268.32243347168, 268.34684753418, 269.30094909668, 268.38786315918, 266.81266784668,
                268.04606628418, 268.37321472168, 267.79118347168, 268.03141784668, 268.58610534668,
                269.61442565918, 270.52946472168, 269.18962097168, 267.19352722168, 266.94938659668,
                268.17497253418, 268.86051940918, 269.12126159668, 268.57145690918, 267.81657409668,
                269.06364440918, 268.13102722168, 267.32926940918, 265.51383972168, 264.53630065918,
                267.12614440918, 265.66227722168, 264.37907409668, 266.34782409668, 266.87809753418,
                266.08805847168, 264.56755065918, 263.26579284668, 263.59782409668, 263.21012878418,
                262.78434753418, 263.64860534668, 264.29704284668, 267.79020690918, 268.02751159668,
                265.11051940918, 266.04118347168, 266.22868347168, 265.68669128418, 265.19157409668,
                265.49235534668, 268.47282409668, 270.01579284668, 268.64469909668, 265.96403503418,
                264.38883972168, 265.86344909668, 267.19255065918, 267.77262878418, 266.39176940918,
                265.06852722168, 267.70622253418, 265.15055847168, 264.67008972168, 262.01383972168,
                260.70036315918, 263.47477722168, 262.19255065918, 260.09880065918, 261.56852722168,
                259.83805847168, 257.34391784668, 257.72770690918, 257.33903503418, 257.53434753418,
                257.98454284668, 256.63200378418, 255.51774597168, 257.18180847168, 262.24040222168,
                263.89176940918, 263.04801940918, 263.22868347168, 260.49821472168, 258.55485534668,
                258.03337097168, 258.44450378418, 262.52360534668, 265.04313659668, 264.70329284668,
                263.59098815918, 261.23063659668, 261.03239440918, 263.51676940918, 265.01286315918,
                263.15934753418, 261.73844909668, 263.92204284668, 258.47282409668, 259.95231628418,
                259.39469909668, 258.83219909668, 258.90055847168, 256.72282409668, 256.31852722168,
                256.54801940918, 250.51872253418, 247.31266784668, 253.01481628418, 256.34684753418,
                255.55973815918, 256.13883972168, 254.51969909668, 250.96598815918, 253.01579284668,
                259.10856628418, 260.65446472168, 259.20036315918, 257.98649597168, 255.03434753418,
                252.78337097168, 251.96012878418, 252.22087097168, 254.66032409668, 256.23747253418,
                257.24235534668, 258.45622253418, 256.85563659668, 255.76676940918, 258.80680847168,
                261.06462097168, 258.76774597168, 256.01676940918, 256.45133972168, 244.57341003418,
                248.43864440918, 253.10661315918, 255.70231628418, 254.26872253418, 251.27458190918,
                251.09977722168, 249.87516784668, 243.36930847168, 240.80192565918, 247.70817565918,
                253.90055847168, 253.57536315918, 250.61051940918, 246.31657409668, 243.27067565918,
                246.93962097168, 254.17301940918, 256.84196472168, 255.08024597168, 252.62712097168,
                249.40837097168, 245.94059753418, 244.67008972168, 246.60856628418, 248.93962097168,
                248.33415222168, 247.41227722168, 249.42399597168, 252.03825378418, 253.44645690918,
                254.10466003418, 252.73161315918, 248.82829284668, 244.93571472168, 243.31950378418,
                239.78337097168, 243.03630065918, 247.24430847168, 249.35856628418, 247.89469909668,
                245.34977722168, 244.31559753418, 242.91325378418, 239.31950378418, 237.10758972168,
                239.24040222168, 242.52653503418, 243.22966003418, 241.56364440918, 239.50895690918,
                239.56559753418, 243.29704284668, 248.37223815918, 250.76481628418, 249.53532409668,
                246.04899597168, 241.46794128418, 237.77165222168, 237.62907409668, 240.78044128418,
                243.01091003418, 241.54606628418, 239.43083190918, 240.96989440918, 245.39762878418,
                248.49919128418, 247.90348815918, 244.65153503418, 241.24821472168, 239.22184753418,
                238.67106628418, 236.89860534668, 237.51872253418, 237.82926940918, 237.34196472168,
                236.14762878418, 235.15153503418, 234.94548034668, 234.94352722168, 234.40544128418,
                233.69841003418, 233.65739440918, 234.35368347168, 235.26872253418, 236.11540222168,
                237.01774597168, 238.20426940918, 239.55387878418, 240.37223815918, 239.89176940918,
                238.00212097168, 235.32243347168, 232.92008972168, 232.04606628418, 233.36637878418,
                235.96794128418, 237.81462097168, 237.84489440918, 237.14567565918, 237.38883972168,
                238.62809753418, 239.40837097168, 238.74040222168, 237.20036315918, 236.04801940918,
                235.85173034668, 236.28239440918, 230.77946472168, 230.08317565918, 229.34977722168,
                228.66911315918, 228.19352722168, 228.05485534668, 228.25602722168, 228.63395690918,
                228.99137878418, 229.24528503418, 229.45622253418, 229.72477722168, 230.09489440918,
                230.53337097168, 230.96012878418, 231.28141784668, 231.41520690918, 231.32731628418,
                231.06169128418, 230.76676940918, 230.67497253418, 231.03141784668, 231.97673034668,
                233.41813659668, 235.00212097168, 236.28825378418, 237.01676940918, 237.21891784668,
                237.07048034668, 236.66227722168, 235.96891784668, 235.00212097168, 233.91520690918,
                232.91325378418, 232.10075378418, 231.42790222168, 227.88688659668, 227.88688659668,
                227.88688659668, 227.88688659668, 227.88688659668, 227.88688659668, 227.88688659668,
                227.88688659668, 227.88688659668, 227.88688659668, 227.88688659668, 227.88688659668,
                227.88688659668, 227.88688659668, 227.88688659668, 227.88688659668, 227.88688659668,
                227.88688659668, 227.88688659668, 227.88688659668, 227.88688659668, 227.88688659668,
                227.88688659668, 227.88688659668, 227.88688659668, 227.88688659668, 227.88688659668,
                227.88688659668, 227.88688659668, 227.88688659668, 227.88688659668, 227.88688659668,
                227.88688659668, 227.88688659668, 227.88688659668, 227.88688659668
            },
            .expectedString = "JumpInfo[version=2,editionNumber=1,binaryScaleFactor=-10,decimalScaleFactor=0,bitsPerValue=16,referenceValue=227.887,offsetBeforeData=103,numberOfDataPoints=684,numberOfValues=684,offsetBeforeBitmap=0,sphericalHarmonics=0,binaryMultiplier=0.000976562,decimalMultiplier=1,totalLength=1476,msgStartOffset=0,md5GridSection=33c7d6025995e1b4913811e77d38ec50,packingType=grid_simple]"
        });
}

void add_simple_synthetic_data() {
    // Surface level grib with bitmask
    testData.push_back(
        InputData{
            .packingType = PackingType::SIMPLE,
            .gribFileName = "sl_mask.grib",
            .expectedData = {
                31.1042442321777, 31.1042442321777, 31.1042442321777, 31.1042442321777, 31.1042442321777,
                31.1042442321777, 31.1042442321777, 31.1042442321777, 31.1042442321777, 31.1042442321777,
                31.1042442321777, 31.1042442321777, 31.1042442321777, 31.1042442321777, 31.1042442321777,
                31.1042442321777, 31.1042442321777, 31.1042442321777, 31.1042442321777, 31.1042442321777,
                31.1042442321777, 31.1042442321777, 31.1042442321777, 31.1042442321777, 31.1042442321777,
                31.1042442321777, 31.1042442321777, 31.1042442321777, 31.1042442321777, 31.1042442321777,
                31.1042442321777, 31.1042442321777, 31.1042442321777, 31.1042442321777, 31.1042442321777,
                31.1042442321777, 34.3005332946777, 34.2819786071777, MISSING_VAL, 34.5856895446777,
                34.5925254821777, 34.6198692321777, 34.3825645446777, 34.2292442321777, 34.3767051696777,
                33.2897911071777, 33.8659629821777, 33.5563926696777, 32.8161582946777, 31.6140098571777,
                31.6794395446777, 30.2009239196777, 29.2614707946777, 30.0808067321777, 30.5358848571777,
                30.2585411071777, 29.8171348571777, 29.4909629821777, 29.0993614196777, 29.8835411071777,
                30.9616661071777, 31.4040489196777, MISSING_VAL, MISSING_VAL, MISSING_VAL,
                32.1628379821777, MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL,
                MISSING_VAL, 33.0319786071777, 35.0485801696777, 35.0788536071777, 34.5690879821777,
                34.3747520446777, 34.7683067321777, 34.5466270446777, MISSING_VAL, MISSING_VAL,
                MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL,
                MISSING_VAL, MISSING_VAL, MISSING_VAL, 25.5280723571777, 27.4782676696777,
                31.2888145446777, 32.6628379821777, MISSING_VAL, MISSING_VAL, 30.6159629821777,
                MISSING_VAL, 30.9177207946777, MISSING_VAL, 30.6423301696777, 30.7497520446777,
                MISSING_VAL, MISSING_VAL, 33.2282676696777, MISSING_VAL, MISSING_VAL,
                MISSING_VAL, 34.1511192321777, 34.8132286071777, 35.1140098571777, MISSING_VAL,
                5.77416610717773, MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL,
                MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL,
                MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, 33.1735801696777,
                33.0358848571777, 33.0573692321777, 30.9851036071777, MISSING_VAL, MISSING_VAL,
                MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL,
                29.6013145446777, 28.0515098571777, MISSING_VAL, 34.1042442321777, 34.4040489196777,
                34.8796348571777, 35.0515098571777, 35.2028770446777, 35.2673301696777, 34.0954551696777,
                MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL,
                MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL,
                MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, 32.8259239196777,
                33.0368614196777, 32.9811973571777, 32.8923301696777, 32.4870567321777, 32.4821739196777,
                32.4616661071777, 32.3464317321777, 32.2731895446777, MISSING_VAL, MISSING_VAL,
                MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, 31.6227989196777,
                34.3991661071777, 35.7175254821777, 35.4157676696777, 35.4284629821777, 35.3034629821777,
                MISSING_VAL, 38.1472129821777, MISSING_VAL, MISSING_VAL, MISSING_VAL,
                MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL,
                MISSING_VAL, MISSING_VAL, 27.9235801696777, 34.0534629821777, MISSING_VAL,
                34.0349082946777, 34.1003379821777, 34.1852989196777, 34.4479942321777, 34.1520957946777,
                33.8981895446777, 33.6345176696777, 33.3923301696777, 32.6394004821777, MISSING_VAL,
                MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, 34.7565879821777,
                36.2936973571777, 36.1716270446777, 36.1745567321777, 36.1726036071777, 35.8991661071777,
                35.1022911071777, MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL,
                MISSING_VAL, 33.4294395446777, MISSING_VAL, MISSING_VAL, MISSING_VAL,
                MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, 34.4372520446777,
                34.6433067321777, 34.8122520446777, 35.0905723571777, 34.9157676696777, 34.9245567321777,
                35.1550254821777, 35.0671348571777, 35.2116661071777, 34.6794395446777, 33.7448692321777,
                33.1374473571777, MISSING_VAL, MISSING_VAL, MISSING_VAL, 36.2966270446777,
                36.8991661071777, 36.9841270446777, 36.9841270446777, 36.9665489196777, 36.9860801696777,
                37.1032676696777, 36.4548301696777, MISSING_VAL, MISSING_VAL, MISSING_VAL,
                MISSING_VAL, 37.1130332946777, MISSING_VAL, 36.4948692321777, 35.4216270446777,
                MISSING_VAL, 32.6501426696777, MISSING_VAL, 33.6052207946777, 34.5241661071777,
                34.6345176696777, 34.8190879821777, 34.9938926696777, 35.1354942321777, 35.3493614196777,
                35.1706504821777, 34.9333457946777, 35.0554161071777, 34.4382286071777, 34.4519004821777,
                34.4704551696777, 34.3464317321777, 34.6345176696777, MISSING_VAL, MISSING_VAL,
                35.9636192321777, 36.2282676696777, 36.5407676696777, 37.4177207946777, 37.3708457946777,
                37.0212364196777, 36.2116661071777, MISSING_VAL, MISSING_VAL, MISSING_VAL,
                MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, 36.3210411071777,
                33.9128379821777, 33.8015098571777, 32.3796348571777, 31.3083457946777, 33.1599082946777,
                33.4372520446777, 33.8513145446777, 34.3737754821777, 34.3259239196777, 34.4636192321777,
                34.7907676696777, 34.6501426696777, 34.6628379821777, 34.5310020446777, 34.6374473571777,
                34.7165489196777, 34.8395957946777, 34.5642051696777, 33.7761192321777, 33.6442832946777,
                33.5368614196777, 36.1755332946777, MISSING_VAL, 34.7087364196777, 30.2038536071777,
                36.2009239196777, 35.9782676696777, 35.8688926696777, MISSING_VAL, 34.0280723571777,
                MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, 35.4255332946777,
                35.3864707946777, 35.2077598571777, 34.3181114196777, 34.1940879821777, MISSING_VAL,
                MISSING_VAL, MISSING_VAL, 34.7907676696777, 34.6433067321777, 34.8737754821777,
                34.9479942321777, 35.4392051696777, 35.3493614196777, 35.2741661071777, 35.2546348571777,
                35.2810020446777, 35.2507286071777, 35.3220176696777, 35.2468223571777, 35.0847129821777,
                35.1208457946777, 33.5114707946777, MISSING_VAL, MISSING_VAL, MISSING_VAL,
                2.32006454467773, 35.8552207946777, 36.1989707946777, 36.2028770446777, 34.3112754821777,
                36.0153770446777, 32.5671348571777, MISSING_VAL, MISSING_VAL, 34.9645957946777,
                35.0427207946777, 34.9333457946777, 34.9733848571777, 34.0476036071777, 34.2458457946777,
                33.7849082946777, 34.0573692321777, MISSING_VAL, 33.3688926696777, 32.6813926696777,
                34.5417442321777, 34.7341270446777, 34.6511192321777, 35.1257286071777, 35.6560020446777,
                36.0192832946777, 36.0319786071777, 35.7917442321777, 35.6335411071777, 35.2956504821777,
                35.0231895446777, 34.9597129821777, 34.9274864196777, 34.8171348571777, MISSING_VAL,
                MISSING_VAL, MISSING_VAL, MISSING_VAL, 36.6218223571777, 36.8308067321777,
                36.6179161071777, 36.2028770446777, 35.4519004821777, MISSING_VAL, MISSING_VAL,
                35.1325645446777, 34.9938926696777, 34.8649864196777, 34.8659629821777, 34.7028770446777,
                34.8571739196777, 34.6462364196777, 34.7429161071777, MISSING_VAL, MISSING_VAL,
                MISSING_VAL, 35.1188926696777, 34.9831504821777, 34.6032676696777, 34.6022911071777,
                35.3591270446777, 35.6940879821777, 35.8366661071777, 36.3776817321777, 36.5407676696777,
                36.6101036071777, 36.3024864196777, 36.0593223571777, 35.7194786071777, 35.4704551696777,
                MISSING_VAL, MISSING_VAL, MISSING_VAL, 37.0085411071777, 37.3142051696777,
                37.0798301696777, 36.6989707946777, 36.0895957946777, 35.7829551696777, MISSING_VAL,
                MISSING_VAL, 35.2380332946777, 35.7341270446777, 35.7263145446777, 35.5544395446777,
                35.7243614196777, 35.9167442321777, 35.8044395446777, 35.5534629821777, MISSING_VAL,
                MISSING_VAL, MISSING_VAL, MISSING_VAL, 35.5524864196777, 35.4577598571777,
                35.0476036071777, 35.3112754821777, 35.4235801696777, 35.4157676696777, 35.2497520446777,
                35.4020957946777, 35.6071739196777, 35.6374473571777, 35.6677207946777, 35.2888145446777,
                34.7429161071777, MISSING_VAL, MISSING_VAL, 35.7761192321777, 36.6198692321777,
                36.2604942321777, 36.1794395446777, 36.2311973571777, 34.6227989196777, 35.3415489196777,
                35.2761192321777, 35.5231895446777, 34.8972129821777, 35.5134239196777, 35.5612754821777,
                35.2585411071777, 34.9528770446777, 34.8640098571777, 34.9489707946777, 35.0563926696777,
                35.1579551696777, 35.0300254821777, 35.3083457946777, 35.5349082946777, 35.4528770446777,
                35.3395957946777, 35.3659629821777, 34.9577598571777, 34.8356895446777, 34.7058067321777,
                34.4753379821777, 34.4538536071777, 34.2097129821777, 34.1667442321777, 34.0886192321777,
                33.9538536071777, 33.9987754821777, MISSING_VAL, 33.9186973571777, 34.8239707946777,
                35.1950645446777, 35.6218223571777, 35.0964317321777, 34.7741661071777, 33.7770957946777,
                33.7653770446777, 33.7888145446777, 33.8366661071777, 33.7487754821777, 33.8083457946777,
                33.8190879821777, 33.8522911071777, 33.8220176696777, 34.0339317321777, 33.9616661071777,
                33.9470176696777, 33.8776817321777, 34.3552207946777, 34.1560020446777, 34.4128379821777,
                34.6677207946777, 34.3503379821777, 34.0183067321777, 34.3142051696777, 34.3503379821777,
                34.5124473571777, 34.4050254821777, 34.3405723571777, 34.2409629821777, 34.1921348571777,
                34.1940879821777, 34.1022911071777, 33.8415489196777, MISSING_VAL, 34.0300254821777,
                33.9645957946777, 33.7585411071777, 33.9724082946777, 33.8737754821777, 33.8278770446777,
                34.0915489196777, 33.7263145446777, 33.7185020446777, 33.7976036071777, 33.7936973571777,
                33.7517051696777, 33.8405723571777, 33.8552207946777, 33.9558067321777, 33.9323692321777,
                33.9870567321777, 33.8649864196777, 33.9372520446777, 33.8425254821777, 33.8308067321777,
                33.8835411071777, 33.9245567321777, 33.8015098571777, 33.8024864196777, 33.8522911071777,
                33.8679161071777, 33.9792442321777, 33.9763145446777, 33.9099082946777, 33.9665489196777,
                33.9890098571777, 34.0563926696777, 34.0671348571777, 34.1120567321777, 33.8698692321777,
                33.7683067321777, 33.8679161071777, 33.7087364196777, 33.8962364196777, 33.9558067321777,
                33.9821739196777, MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL,
                MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL,
                MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL,
                MISSING_VAL, MISSING_VAL, MISSING_VAL, 34.2429161071777, 34.0397911071777,
                34.0212364196777, 33.9020957946777, 33.8561973571777, 33.9489707946777, 33.7487754821777,
                33.5368614196777, 33.3181114196777, 33.7595176696777, 33.8591270446777, 33.9958457946777,
                MISSING_VAL, 34.0944786071777, 33.8981895446777, 33.8395957946777, 34.1931114196777,
                34.1950645446777, 33.9011192321777, MISSING_VAL, MISSING_VAL, MISSING_VAL,
                MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL,
                MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL,
                MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL,
                MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL,
                MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL,
                MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL,
                MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL,
                MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL,
                MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL,
                MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL,
                MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL,
                MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL,
                MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL,
                MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL
            },
            .expectedString = "JumpInfo[version=2,editionNumber=1,binaryScaleFactor=-10,decimalScaleFactor=0,bitsPerValue=16,referenceValue=2.32006,offsetBeforeData=195,numberOfDataPoints=684,numberOfValues=439,offsetBeforeBitmap=98,sphericalHarmonics=0,binaryMultiplier=0.000976562,decimalMultiplier=1,totalLength=1078,msgStartOffset=0,md5GridSection=33c7d6025995e1b4913811e77d38ec50,packingType=grid_simple]",
        });
}


void add_simple_synthetic_data2() {
    std::vector<double> expectedData = {
        0, MISSING_VAL, MISSING_VAL, 3, 4, MISSING_VAL, MISSING_VAL, MISSING_VAL, 8, 9,
        10, MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, 15, 16, 17, 18, MISSING_VAL,
        MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, 24, 25, 26, 27, 28, MISSING_VAL,
        MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, 35, 36, 37, 38, 39,
        40, MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, 48, 49,
        50, 51, 52, 53, 54, MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL,
        MISSING_VAL, MISSING_VAL, MISSING_VAL, 63, 64, 65, 66, 67, 68, 69,
        70, MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL,
        80, 81, 82, 83, 84, 85, 86, 87, 88, MISSING_VAL,
        MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, 99,
        100, 101, 102, 103, 104, 105, 106, 107, 108, MISSING_VAL,
        MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL,
        120, 121, 122, 123, 124, 125, 126, 127, 128, 129,
        130, MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL,
        MISSING_VAL, MISSING_VAL, MISSING_VAL, 143, 144, 145, 146, 147, 148, 149,
        150, 151, 152, 153, 154, MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL,
        MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, 168, 169,
        170, 171, 172, 173, 174, 175, 176, 177, 178, 179,
        180, MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL,
        MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, 195, 196, 197, 198, 199,
        200, 201, 202, 203, 204, 205, 206, 207, 208, MISSING_VAL,
        MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL,
        MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, 224, 225, 226, 227, 228, 229,
        230, 231, 232, 233, 234, 235, 236, 237, 238, MISSING_VAL,
        MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL,
        MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, 255, 256, 257, 258, 259,
        260, 261, 262, 263, 264, 265, 266, 267, 268, 269,
        270, MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL,
        MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, 288, 289,
        290, 291, 292, 293, 294, 295, 296, 297, 298, 299,
        300, 301, 302, 303, 304, MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL,
        MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL,
        MISSING_VAL, MISSING_VAL, MISSING_VAL, 323, 324, 325, 326, 327, 328, 329,
        330, 331, 332, 333, 334, 335, 336, 337, 338, 339,
        340, MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL,
        MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL,
        360, 361, 362, 363, 364, 365, 366, 367, 368, 369,
        370, 371, 372, 373, 374, 375, 376, 377, 378, MISSING_VAL,
        MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL,
        MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, 399,
        400, 401, 402, 403, 404, 405, 406, 407, 408, 409,
        410, 411, 412, 413, 414, 415, 416, 417, 418, MISSING_VAL,
        MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL,
        MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL,
        440, 441, 442, 443, 444, 445, 446, 447, 448, 449,
        450, 451, 452, 453, 454, 455, 456, 457, 458, 459,
        460, MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL,
        MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL,
        MISSING_VAL, MISSING_VAL, MISSING_VAL, 483, 484, 485, 486, 487, 488, 489,
        490, 491, 492, 493, 494, 495, 496, 497, 498, 499,
        500, 501, 502, 503, 504, MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL,
        MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL,
        MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, 528, 529,
        530, 531, 532, 533, 534, 535, 536, 537, 538, 539,
        540, 541, 542, 543, 544, 545, 546, 547, 548, 549,
        550, MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL,
        MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL,
        MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, 575, 576, 577, 578, 579,
        580, 581, 582, 583, 584, 585, 586, 587, 588, 589,
        590, 591, 592, 593, 594, 595, 596, 597, 598, MISSING_VAL,
        MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL,
        MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL,
        MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, 624, 625, 626, 627, 628, 629,
        630, 631, 632, 633, 634, 635, 636, 637, 638, 639,
        640, 641, 642, 643, 644, 645, 646, 647, 648, MISSING_VAL,
        MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL,
        MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL,
        MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, MISSING_VAL, 675, 676, 677, 678, 679,
        680, 681, 682, 683
    };


    testData.push_back(InputData{
        .packingType = PackingType::SIMPLE,
        //.gribFileName = "synth11.grib",
        .gribFileName = "./data/synth11_simple_bitmap.grib2",
        .expectedData = expectedData,
        .expectedString = "JumpInfo[version=2,editionNumber=1,binaryScaleFactor=-1,decimalScaleFactor=0,bitsPerValue=11,referenceValue=0,offsetBeforeData=195,numberOfDataPoints=684,numberOfValues=334,offsetBeforeBitmap=98,sphericalHarmonics=0,binaryMultiplier=0.5,decimalMultiplier=1,totalLength=660,msgStartOffset=0,md5GridSection=33c7d6025995e1b4913811e77d38ec50,packingType=grid_simple]"
    });

    testData.push_back(InputData{
        .packingType = PackingType::CCSDS,
        .gribFileName = "./data/synth11_ccsds_bitmap.grib2",
        .expectedData = expectedData,
        .expectedString = "JumpInfo[version=2,editionNumber=1,binaryScaleFactor=-1,decimalScaleFactor=0,bitsPerValue=11,referenceValue=0,offsetBeforeData=195,numberOfDataPoints=684,numberOfValues=334,offsetBeforeBitmap=98,sphericalHarmonics=0,binaryMultiplier=0.5,decimalMultiplier=1,totalLength=660,msgStartOffset=0,md5GridSection=33c7d6025995e1b4913811e77d38ec50,packingType=grid_simple]"
    });

    testData.push_back(InputData{
        .packingType = PackingType::SIMPLE,
        .gribFileName = "synth12.grib",
        .expectedData = expectedData,
        .expectedString = "JumpInfo[version=2,editionNumber=1,binaryScaleFactor=-2,decimalScaleFactor=0,bitsPerValue=12,referenceValue=0,offsetBeforeData=195,numberOfDataPoints=684,numberOfValues=334,offsetBeforeBitmap=98,sphericalHarmonics=0,binaryMultiplier=0.25,decimalMultiplier=1,totalLength=700,msgStartOffset=0,md5GridSection=33c7d6025995e1b4913811e77d38ec50,packingType=grid_simple]"
    });

    // Grib with single value
    testData.push_back(InputData{
        .packingType = PackingType::SIMPLE,
        .gribFileName = "const.grib",
        .expectedData = std::vector<double>(expectedData.size(), 1.23456789),
        .epsilon = 1e-6, // Constant fields are stored at reduced precision
        .expectedString = "JumpInfo[version=2,editionNumber=1,binaryScaleFactor=-10,decimalScaleFactor=0,bitsPerValue=0,referenceValue=1.23457,offsetBeforeData=111,numberOfDataPoints=684,numberOfValues=1,offsetBeforeBitmap=98,sphericalHarmonics=0,binaryMultiplier=0.000976562,decimalMultiplier=1,totalLength=116,msgStartOffset=0,md5GridSection=33c7d6025995e1b4913811e77d38ec50,packingType=grid_simple]"
    });
}

void setGribJumpData() {
// Set the data used by the test cases
    add_simple_no_bitmask();
    add_simple_synthetic_data();
    add_simple_synthetic_data2();
}

