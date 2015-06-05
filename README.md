# easystring

std::string s1 = $("hello world!");
std::string s3 = $(10.01f);
std::string s4 = $(false);
std::string s5 = $ + "hello" + " world" + " zg " + 10 + " " + false;

auto a = $int.parse("100");
auto b = $float.parse("100.1");
auto c = $double.parse("100.1");
auto d = $bool.parse("false"); //空值，"0"及"false"以外都是true

auto v0 = $.split("hello world zg", " ");
auto v1 = $int.split("1,200;2,400", ",;");
auto v2 = $float.split("1,200.01,2,400.02", ",");
auto v3 = $double.split("1,200.01;2,400.02", ",;");
auto v4 = $bool.split("0,false;1,true", ",;");

$.log("format: %d", 10);
auto s2 = $.format("hello world %s %d!", "zg", 10);
auto v5 = $.split("hello world zg", " ");
auto s6 = $.join(v4, ",;").str();
auto s7 = $.join({1, 2, 3, 4}, ",").str();
auto s9 = $.join({1, false, 2, 3, "1", 2, 10.01,}, ",").str();
$.log("%s", s9.c_str());

auto xx = $[{1, 2, 3}];
$.log("%s", xx.str().c_str());

auto yy = $({
    "1", 2,
    "3", $[{1, 2, 3}],
    "5", false,
    "xx", "yy"
});

$.log("%s", yy.str().c_str());

std::string zz = $({
    "1", $[{1, 2, 3}],
    "2", $({
        "1", 2,
        "3", $[{s1, $[{"a", "b", "c", $[{"d", "e", "f", $[{"a", "b", "c"}]}]}], s3, false}],
        "5", false,
        "xx", "yy"
    }),
    "3", false
});

$.log("%s", zz.c_str());


$assert(s1 == "hello world!", "");
$assert(s3 == "10.01", "");
$assert(s4 == "false", "");
$assert(s5 == "hello world zg 10 false", "");
$assert(s2 == "hello world zg 10!", "");
$assert(s6 == "false,false;true,true", "");

$assert(a == 100, "");
$assert(b == 100.1f, "");
$assert(c == 100.1, "");
$assert(d == false, "");

$assert(v0.size() == 3, "");
$assert(v1.size() == 4, "");
$assert(v2.size() == 4, "");
$assert(v3.size() == 4, "");
$assert(v4.size() == 4, "");
$assert(v5.size() == 3, "");

$assert(xx.str() == "[1,2,3]", "");
$assert(yy.str() == "{\"1\":2,\"3\":[1,2,3],\"5\":false,\"xx\":\"yy\"}", "");
$assert(yy.str() == "{\"1\":2,\"3\":[1,2,3],\"5\":false,\"xx\":\"yy\"}", "");

$assert(false, "end of my test: %s", "good");
