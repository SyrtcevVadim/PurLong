
#define CATCH_CONFIG_ENABLE_BENCHMARKING
// Раскомментировать, если нужны бенчмарки
//#define PURLONG_ENABLE_BENCHMARKS
#include "../third_party/catch.hpp"
#include "../src/purlong.h"
#include <vector>
#include <string>
using namespace std;


TEST_CASE("unary +")
{
    auto number = GENERATE("0", "-123","1234327980432097809423172143");
    CHECK(+PurLong(number) == PurLong(number));
}

TEST_CASE("unary -")
{
    vector<string> initial{
        "0",
        "1",
        "-1",
        "430298103492187432987439874923084023949324719328947238904348749172473014789047928347"
    };
    vector<string> answer{
        "0",
        "-1",
        "1",
        "-430298103492187432987439874923084023949324719328947238904348749172473014789047928347"
    };

    for(int i{0}; i < initial.size(); i++)
    {
        CHECK(-PurLong(initial[i]) == PurLong(answer[i]));
    }
}

TEST_CASE("binary +")
{
    SECTION("positive numbers")
    {
        vector<string> lValue
        {"1",
        "2",
        "78",
        "999999999999999",
        "107984324980312746832976480392342480937124907309483246738216498126443128697631428978787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878788432671843278946328961489723641333313131313131313131313131313131313131313131313131314732819888898989898989898989898989898989898989898989884321786947683214876413687964837291784312781349985987632489461372453126845237164983216478932649812364876123941210798432498031274683297648039234248093712490730948324673821649812644312869763142897878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878843267184327894632896148972364133331313131313131313131313131313131313131313131313131473281988889898989898989898989898989898989898989898988432178694768321487641368796483729178431278134998598763248946137245312684523716498321647893264981236487612394121079843249803127468329764803923424809371249073094832467382164981264431286976314289787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787884326718432789463289614897236413333131313131313131313131313131313131313131313131313147328198888989898989898989898989898989898989898989898843217869476832148764136879648372917843127813499859876324894613724531268452371649832164789326498123648761239412107984324980312746832976480392342480937124907309483246738216498126443128697631428978787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878788432671843278946328961489723641333313131313131313131313131313131313131313131313131314732819888898989898989898989898989898989898989898989884321786947683214876413687964837291784312781349985987632489461372453126845237164983216478932649812364876123941210798432498031274683297648039234248093712490730948324673821649812644312869763142897878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878843267184327894632896148972364133331313131313131313131313131313131313131313131313131473281988889898989898989898989898989898989898989898988432178694768321487641368796483729178431278134998598763248946137245312684523716498321647893264981236487612394121079843249803127468329764803923424809371249073094832467382164981264431286976314289787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787884326718432789463289614897236413333131313131313131313131313131313131313131313131313147328198888989898989898989898989898989898989898989898843217869476832148764136879648372917843127813499859876324894613724531268452371649832164789326498123648761239412"};
        vector<string> rValue
        {"324", 
        "32423432",
        "2", 
        "999999999999999999999911111111111111111111",
        "107984324980312746832976480392342480937124907309483246738216498126443128697631428978787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878788432671843278946328961489723641333313131313131313131313131313131313131313131313131314732819888898989898989898989898989898989898989898989884321786947683214876413687964837291784312781349985987632489461372453126845237164983216478932649812364876123941210798432498031274683297648039234248093712490730948324673821649812644312869763142897878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878843267184327894632896148972364133331313131313131313131313131313131313131313131313131473281988889898989898989898989898989898989898989898988432178694768321487641368796483729178431278134998598763248946137245312684523716498321647893264981236487612394121079843249803127468329764803923424809371249073094832467382164981264431286976314289787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787884326718432789463289614897236413333131313131313131313131313131313131313131313131313147328198888989898989898989898989898989898989898989898843217869476832148764136879648372917843127813499859876324894613724531268452371649832164789326498123648761239412107984324980312746832976480392342480937124907309483246738216498126443128697631428978787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878788432671843278946328961489723641333313131313131313131313131313131313131313131313131314732819888898989898989898989898989898989898989898989884321786947683214876413687964837291784312781349985987632489461372453126845237164983216478932649812364876123941210798432498031274683297648039234248093712490730948324673821649812644312869763142897878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878843267184327894632896148972364133331313131313131313131313131313131313131313131313131473281988889898989898989898989898989898989898989898988432178694768321487641368796483729178431278134998598763248946137245312684523716498321647893264981236487612394121079843249803127468329764803923424809371249073094832467382164981264431286976314289787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787878787884326718432789463289614897236413333131313131313131313131313131313131313131313131313147328198888989898989898989898989898989898989898989898843217869476832148764136879648372917843127813499859876324894613724531268452371649832164789326498123648761239412"};
        vector<string> resultSum
        {"325",
        "32423434",
        "80", 
        "999999999999999999999911112111111111111110",
        "215968649960625493665952960784684961874249814618966493476432996252886257395262857957575757575757575757575757575757575757575757575757575757575757575757575757575757575757575757575757575757575757575757575757575757575757575757575757575757575757575757575757575757575757575757576865343686557892657922979447282666626262626262626262626262626262626262626262626262629465639777797979797979797979797979797979797979797979768643573895366429752827375929674583568625562699971975264978922744906253690474329966432957865299624729752247882421596864996062549366595296078468496187424981461896649347643299625288625739526285795757575757575757575757575757575757575757575757575757575757575757575757575757575757575757575757575757575757575757575757575757575757575757575757575757575757575757575757575757575757575757575757686534368655789265792297944728266662626262626262626262626262626262626262626262626262946563977779797979797979797979797979797979797979797976864357389536642975282737592967458356862556269997197526497892274490625369047432996643295786529962472975224788242159686499606254936659529607846849618742498146189664934764329962528862573952628579575757575757575757575757575757575757575757575757575757575757575757575757575757575757575757575757575757575757575757575757575757575757575757575757575757575757575757575757575757575757575757575768653436865578926579229794472826666262626262626262626262626262626262626262626262626294656397777979797979797979797979797979797979797979797686435738953664297528273759296745835686255626999719752649789227449062536904743299664329578652996247297522478824215968649960625493665952960784684961874249814618966493476432996252886257395262857957575757575757575757575757575757575757575757575757575757575757575757575757575757575757575757575757575757575757575757575757575757575757575757575757575757575757575757575757575757575757575757576865343686557892657922979447282666626262626262626262626262626262626262626262626262629465639777797979797979797979797979797979797979797979768643573895366429752827375929674583568625562699971975264978922744906253690474329966432957865299624729752247882421596864996062549366595296078468496187424981461896649347643299625288625739526285795757575757575757575757575757575757575757575757575757575757575757575757575757575757575757575757575757575757575757575757575757575757575757575757575757575757575757575757575757575757575757575757686534368655789265792297944728266662626262626262626262626262626262626262626262626262946563977779797979797979797979797979797979797979797976864357389536642975282737592967458356862556269997197526497892274490625369047432996643295786529962472975224788242159686499606254936659529607846849618742498146189664934764329962528862573952628579575757575757575757575757575757575757575757575757575757575757575757575757575757575757575757575757575757575757575757575757575757575757575757575757575757575757575757575757575757575757575757575768653436865578926579229794472826666262626262626262626262626262626262626262626262626294656397777979797979797979797979797979797979797979797686435738953664297528273759296745835686255626999719752649789227449062536904743299664329578652996247297522478824"};

        for(int i{0}; i<lValue.size(); i++)
        {
            CHECK(PurLong(lValue[i])+PurLong(rValue[i])==PurLong(resultSum[i]));
        }
    }
    #ifdef PURLONG_ENABLE_BENCHMARKS
    SECTION("benchmarks")
    {
        // готовим данные
        string a{};
        for(int i{0}; i < 334; i++)
        {
            a += "999999999";
        }
        BENCHMARK("sum of two 3000-digit numbers")
        {
            return (PurLong(a)+PurLong(a));
        };
    }
    #endif
}

TEST_CASE("binary -")
{
    SECTION("positive numbers")
    {
        vector<string> lValue{
            "1",
            "1234567891",
            "55555555555555555",
            "100000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
            "10010110031422222222222222222242434321111111111114321789632187943289763428674382697143268794386794632784766321643927641001011003142222222222222222224243432111111111111432178963218794328976342867438269714326879438679463278476632164392761001011003142222222222222222224243432111111111111432178963218794328976342867438269714326879438679463278476632164392764410010110031422222222222222222242434321111111111114321789632187943289763428674382697143268794386794632784766321643927641001011003142222222222222222224243432111111111111432178963218794328976342867438269714326879438679463278476632164392764100101100314222222222222222222424343211111111111143217896321879432897634286743826971432687943867946327847663216439276410010110031422222222222222222242434321111111111114321789632187943289763428674382697143268794386794632784766321643927641001011003142222222222222222224243432111111111111432178963218794328976342867438269714326879438679463278476632164392764100101100314222222222222222222424343211111111111143217896321879432897634286743826971432687943867946327847663216439276410010110031422222222222222222242434321111111111114321789632187943289763428674382697143268794386794632784766321643927641001011003142222222222222222224243432111111111111432178963218794328976342867438269714326879438679463278476632164392764100101100314222222222222222222424343211111111111143217896321879432897634286743826971432687943867946327847663216439276410010110031422222222222222222242434321111111111114321789632187943289763428674382697143268794386794632784766321643927641001011003142222222222222222224243432111111111111432178963218794328976342867438269714326879438679463278476632164392764100101100314222222222222222222424343211111111111143217896321879432897634286743826971432687943867946327847663216439276410010110031422222222222222222242434321111111111114321789632187943289763428674382697143268794386794632784766321643927641001011003142222222222222222224243432111111111111432178963218794328976342867438269714326879438679463278476632164392764100101100314222222222222222222424343211111111111143217896321879432897634286743826971432687943867946327847663216439276410010110031422222222222222222242434321111111111114321789632187943289763428674382697143268794386794632784766321643927641001011003142222222222222222224243432111111111111432178963218794328976342867438269714326879438679463278476632164392764100101100314222222222222222222424343211111111111143217896321879432897634286743826971432687943867946327847663216439276410010110031422222222222222222242434321111111111114321789632187943289763428674382697143268794386794632784766321643927641001011003142222222222222222224243432111111111111432178963218794328976342867438269714326879438679463278476632164392764100101100314222222222222222222424343211111111111143217896321879432897634286743826971432687943867946327847663216439276410010110031422222222222222222242434321111111111114321789632187943289763428674382697143268794386794632784766321643927641001011003142222222222222222224243432111111111111432178963218794328976342867438269714326879438679463278476632164392764"
        };

        vector<string> rValue{
            "1",
            "999999999999999999999999999",
            "99999999999999",
            "123456789123456789123456789123456789123456789123456789123456789123456789123456789",
            "10010110031422222222222222222242434321111111111114321789632187943289763428674382697143268794386794632784766321643927641001011003142222222222222222224243432111111111111432178963218794328976342867438269714326879438679463278476632164392761001011003142222222222222222224243432111111111111432178963218794328976342867438269714326879438679463278476632164392764410010110031422222222222222222242434321111111111114321789632187943289763428674382697143268794386794632784766321643927641001011003142222222222222222224243432111111111111432178963218794328976342867438269714326879438679463278476632164392764100101100314222222222222222222424343211111111111143217896321879432897634286743826971432687943867946327847663216439276410010110031422222222222222222242434321111111111114321789632187943289763428674382697143268794386794632784766321643927641001011003142222222222222222224243432111111111111432178963218794328976342867438269714326879438679463278476632164392764100101100314222222222222222222424343211111111111143217896321879432897634286743826971432687943867946327847663216439276410010110031422222222222222222242434321111111111114321789632187943289763428674382697143268794386794632784766321643927641001011003142222222222222222224243432111111111111432178963218794328976342867438269714326879438679463278476632164392764100101100314222222222222222222424343211111111111143217896321879432897634286743826971432687943867946327847663216439276410010110031422222222222222222242434321111111111114321789632187943289763428674382697143268794386794632784766321643927641001011003142222222222222222224243432111111111111432178963218794328976342867438269714326879438679463278476632164392764100101100314222222222222222222424343211111111111143217896321879432897634286743826971432687943867946327847663216439276410010110031422222222222222222242434321111111111114321789632187943289763428674382697143268794386794632784766321643927641001011003142222222222222222224243432111111111111432178963218794328976342867438269714326879438679463278476632164392764100101100314222222222222222222424343211111111111143217896321879432897634286743826971432687943867946327847663216439276410010110031422222222222222222242434321111111111114321789632187943289763428674382697143268794386794632784766321643927641001011003142222222222222222224243432111111111111432178963218794328976342867438269714326879438679463278476632164392764100101100314222222222222222222424343211111111111143217896321879432897634286743826971432687943867946327847663216439276410010110031422222222222222222242434321111111111114321789632187943289763428674382697143268794386794632784766321643927641001011003142222222222222222224243432111111111111432178963218794328976342867438269714326879438679463278476632164392764100101100314222222222222222222424343211111111111143217896321879432897634286743826971432687943867946327847663216439276410010110031422222222222222222242434321111111111114321789632187943289763428674382697143268794386794632784766321643927641001011003142222222222222222224243432111111111111432178963218794328976342867438269714326879438679463278476632164392764"
        };

        vector<string> resultDifference{
            "0",
            "-999999999999999998765432108",
            "55455555555555556",
            "99999999999999999999999999999999999999999999999999876543210876543210876543210876543210876543210876543210876543210876543210876543211",
            "0"
        };

        for(int i{0}; i < lValue.size(); i++)
        {
            INFO(i);
            CHECK(PurLong(lValue[i])-PurLong(rValue[i]) == PurLong(resultDifference[i]));
        }
    }
    #ifdef PURLONG_ENABLE_BENCHMARKS
    SECTION("benchmarks")
    {

        BENCHMARK("difference of 3000-digit number and 2500-digit number")
        {
            return (PurLong("1000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000")
            -
            PurLong("19999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999")
            );
        };
        // Готовим данные 
        // Эта бенчмарка занимает порядка 3.5 минут, поэтому закомментирована
        // string lValue{};
        // for(int i{0}; i < 1'000'000; i++)
        // {
        //     lValue += "9";
        // }
        // string rValue{};
        // for(int i{0}; i < 111'111; i++)
        // {
        //     rValue+="123456789";
        // }
        // BENCHMARK("difference of two 1'000'000-digit numbers")
        // {
        //     return(PurLong(lValue)-PurLong(rValue));
        // };
    }
    #endif
}