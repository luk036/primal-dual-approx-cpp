#include <pldl/netlist.hpp> // import Netlist
#include <pldl/netlist_algo.hpp> // import Netlist
#include <doctest.h>
#include <memory> //std::unique_ptr
#include <py2cpp/py2cpp.hpp>
#include <string_view>

extern SimpleNetlist create_test_netlist(); // import create_test_netlist
extern SimpleNetlist create_dwarf();        // import create_dwarf
extern SimpleNetlist readNetD(std::string_view netDFileName);
extern void readAre(SimpleNetlist& H, std::string_view areFileName);
// extern std::tuple<py::set<node_t>, int>
// min_net_cover_pd(SimpleNetlist &, const std::vector<int> &);

using node_t = SimpleNetlist::node_t;

//
// Primal-dual algorithm for minimum vertex cover problem
//

// TEST_CASE("Test min_net_cover_pd dwarf", "[test_min_cover]") {
//     auto H = create_dwarf();
//     auto [S, cost] = min_net_cover_pd(H, H.module_weight);
//     CHECK(cost == 3);
// }

// TEST_CASE("Test min_net_cover_pd ibm01", "[test_min_cover]") {
//     auto H = readNetD("../../../testcases/ibm01.net");
//     readAre(H, "../../../testcases/ibm01.are");
//     auto [S, cost] = min_net_cover_pd(H, H.net_weight);
//     CHECK(cost == 4053);
// }

TEST_CASE("Test min_maximal_matching dwarf")
{
    const auto H = create_dwarf();
    // const auto N = H.number_of_nets();
    auto matchset = py::dict<node_t, bool>{};
    auto dep = py::dict<node_t, bool>{};
    for (auto net : H.nets)
    {
        matchset[net] = false;
        dep[net] = false;
    }
    const auto rslt =
        min_maximal_matching(H, H.module_weight, matchset, dep);
    CHECK(rslt == 33);
}

// TEST_CASE("Test min_maximal_matching ibm01") {
//     auto H = readNetD("../../../testcases/ibm01.net");
//     readAre(H, "../../../testcases/ibm01.are");
//     auto [S, cost] = min_maximal_matching(H, H.net_weight);
//     CHECK(cost == 3157);
// }

