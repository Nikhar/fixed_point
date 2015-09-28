///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2015.
//  Copyright Nikhar Agrawal 2015.
//  Copyright Paul Bristow 2015.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)

//! \file
//!\brief Tests for the trogonometric arcsine function of (fixed_point) for a big digit range.

#include <array>
#include <string>

#define BOOST_TEST_MODULE test_negatable_trig_func_arctangent_big
#define BOOST_LIB_DIAGNOSTIC

#include <boost/fixed_point/fixed_point.hpp>
#include <boost/test/included/unit_test.hpp>

namespace local
{
  // Table[N[ArcTan[n / 10], 40], {n, 0, 80, 1}]
  const std::array<std::string, 81U> data =
  {{
    std::string("0.0"),
    std::string("0.099668652491162027378446119878020590243"),
    std::string("0.197395559849880758370049765194790293448"),
    std::string("0.291456794477867091995604621432891193503"),
    std::string("0.380506377112364886303587916810433104497"),
    std::string("0.463647609000806116214256231461214402029"),
    std::string("0.540419500270584155443578364608599910135"),
    std::string("0.610725964389208616543758876490236093819"),
    std::string("0.674740942223552663056520973609813615074"),
    std::string("0.732815101786506591640792072734280251986"),
    std::string("0.785398163397448309615660845819875721049"),
    std::string("0.832981266674431705417693561836361238516"),
    std::string("0.876058050598193423114047521128341339075"),
    std::string("0.915100700553360416566801972455272966548"),
    std::string("0.950546840812075147894789135463819175048"),
    std::string("0.982793723247329067985710611014666014497"),
    std::string("1.012197011451334183259813475238090171752"),
    std::string("1.039072259536091027621250337907278845312"),
    std::string("1.063697822402559660943891116052545478563"),
    std::string("1.086318397757873418063979581925677628976"),
    std::string("1.107148717794090503017065460178537040070"),
    std::string("1.126377116893797709896417672751453253721"),
    std::string("1.144168833668020530011580909746336220826"),
    std::string("1.160668986253405626780110920784532177186"),
    std::string("1.176005207095135102491222161250170855203"),
    std::string("1.190289949682531732927733774829318337601"),
    std::string("1.203622492976677410806832674846875783398"),
    std::string("1.216090674783956302858926321341137794810"),
    std::string("1.227772386374193222157793092225941825411"),
    std::string("1.238736859252011141377960254388087359074"),
    std::string("1.249045772398254425829917077281090123078"),
    std::string("1.258754205232363325559837795038327919480"),
    std::string("1.267911458419925213670765597134193228807"),
    std::string("1.276561761683708842478388634840370931522"),
    std::string("1.284744885077578395216600450355761244835"),
    std::string("1.292496667789785267903091421407081684585"),
    std::string("1.299849476456476077794726187689133329919"),
    std::string("1.306832603169192056662625232150990081553"),
    std::string("1.313472611823807976429456612583439739219"),
    std::string("1.319793640151862014788982811835446489256"),
    std::string("1.325817663668032465059239210428475631184"),
    std::string("1.331564726831236050175290558731846965712"),
    std::string("1.337053145925995194208639620436563514373"),
    std::string("1.342299687503034311896298710207680433429"),
    std::string("1.347319725654263598157642276990163839691"),
    std::string("1.352127380920954657189147941389812850984"),
    std::string("1.356735643231075112363641237290721354020"),
    std::string("1.361156480920684098603062396819136900490"),
    std::string("1.365400937605129227106169150226454233290"),
    std::string("1.369479218420255859173795144121223718097"),
    std::string("1.373400766945015860861271926444961148651"),
    std::string("1.377174333938951237114529917357234396320"),
    std::string("1.380808038876180896064204625161783281235"),
    std::string("1.384309425127679843049373326777465189940"),
    std::string("1.387685509532412491297783540024108631049"),
    std::string("1.390942827002418348642768694383643206086"),
    std::string("1.394087470724860004511420349984935736772"),
    std::string("1.397125128453322791491610200281568692208"),
    std::string("1.400061115319613814504124238644519364455"),
    std::string("1.402900403544522051597963459641226717697"),
    std::string("1.405647649380269780952193401995807988100"),
    std::string("1.408307217577693245323149617056105478699"),
    std::string("1.410883203636677350091331243841584636461"),
    std::string("1.413379454068305902274849776074336552248"),
    std::string("1.415799584870955636927607316706259251043"),
    std::string("1.418146998399631459403860303970098952372"),
    std::string("1.420424898787762079618672902892785583210"),
    std::string("1.422636306063065240746098787118089651846"),
    std::string("1.424784069083621217944335150102383520937"),
    std::string("1.426870877406680315428496325621425796000"),
    std::string("1.428899272190732696418470074537198359091"),
    std::string("1.430871656220778869368380132845421137263"),
    std::string("1.432790303137377172009085030907497253625"),
    std::string("1.434657365941755859085555737530002609422"),
    std::string("1.436474884841928111618379082638537737160"),
    std::string("1.438244794498222597961404247935481585539"),
    std::string("1.439968930720839665059918620738932215749"),
    std::string("1.441649036666876559602128650874979404800"),
    std::string("1.443286768579658360156252414429454254735"),
    std::string("1.444883701109098402129173983761636875775"),
    std::string("1.446441332248135184199966842475880416525")
  }};

  // N[ArcTan[256], 40].
  // 1.566890096662929647403693026328327054958
}

BOOST_AUTO_TEST_CASE(test_negatable_trig_func_arctangent_big)
{
  typedef boost::fixed_point::negatable<10, -117> fixed_point_type;
  typedef fixed_point_type::float_type            float_point_type;

  const fixed_point_type tol = ldexp(fixed_point_type(1), fixed_point_type::resolution + 12);

  // Check positive arguments.
  for(int i = 0; i < int(local::data.size() - 1); ++i)
  {
    const fixed_point_type x = atan(fixed_point_type(i) / 10);
    const float_point_type y = float_point_type(local::data[i]);

    BOOST_CHECK_CLOSE_FRACTION(x, fixed_point_type(y), tol);
  }

  // Check negative arguments.
  for(int i = 0; i < int(local::data.size() - 1); ++i)
  {
    const fixed_point_type x = atan(fixed_point_type(-i) / 10);
    const float_point_type y = -float_point_type(local::data[i]);

    BOOST_CHECK_CLOSE_FRACTION(x, fixed_point_type(y), tol);
  }

  // Check a larger argument.
  {
    const fixed_point_type x = atan(fixed_point_type(256));
    const float_point_type y = float_point_type("1.566890096662929647403693026328327054958");

    BOOST_CHECK_CLOSE_FRACTION(x, fixed_point_type(y), tol);
  }
}
