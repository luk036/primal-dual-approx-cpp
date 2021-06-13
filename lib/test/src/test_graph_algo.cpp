#include <doctest.h>
#include <pldl/graph_algo.hpp> // import Netlist
#include <pldl/netlist.hpp>    // import Netlist
#include <py2cpp/py2cpp.hpp>
#include <string_view>

extern auto create_test_netlist()
    -> SimpleNetlist;                        // import create_test_netlist
extern auto create_dwarf() -> SimpleNetlist; // import create_dwarf
extern auto readNetD(std::string_view netDFileName) -> SimpleNetlist;
extern void readAre(SimpleNetlist& H, std::string_view areFileName);

using node_t = SimpleNetlist::node_t;

//
// Primal-dual algorithm for minimum vertex cover problem
//
TEST_CASE("Test min_vertex_cover dwarf")
{
    const auto H = create_dwarf();
    auto weight = py::dict<node_t, int> {};
    auto covset = py::set<node_t> {};
    for (auto node : H.G)
    {
        weight[node] = 1;
        // covset[node] = false;
    }
    auto rslt = pldl::min_vertex_cover(H.G, weight, covset);
    CHECK(rslt >= 7);
    CHECK(rslt <= 9);
}

TEST_CASE("Test min_maximal_independent_set dwarf")
{
    const auto H = create_dwarf();
    auto weight = py::dict<node_t, int> {};
    auto indset = py::set<node_t> {};
    auto dep = py::set<node_t> {};
    for (auto node : H.G)
    {
        weight[node] = 1;
        // indset[node] = false;
        // dep[node] = false;
    }
    auto rslt = pldl::min_maximal_independant_set(H.G, weight, indset, dep);
    CHECK(rslt == 7);
}

// TEST_CASE("Test min_maximal_matching ibm01") {
//     auto H = readNetD("../../../testcases/ibm01.net");
//     readAre(H, "../../../testcases/ibm01.are");
//     auto [S, cost] = min_maximal_matching(H, H.net_weight);
//     CHECK(cost == 3157);
// }
