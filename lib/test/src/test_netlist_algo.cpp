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

TEST_CASE("Test min_vertex_cover dwarf")
{
    const auto H = create_dwarf();
    auto weight = py::dict<node_t, int>{};
    auto covset = py::dict<node_t, bool>{};
    for (auto node : H.modules) {
        weight[node] = 1;
        covset[node] = false;
    }
    auto rslt = pldl::min_vertex_cover(H, weight, covset);
    CHECK(rslt == 4);
}

//
// Primal-dual algorithm for minimum vertex cover problem
//


TEST_CASE("Test min_maximal_matching dwarf")
{
    const auto H = create_dwarf();
    // const auto N = H.number_of_nets();
    auto matchset = py::dict<node_t, bool>{};
    auto weight = py::dict<node_t, int>{};
    auto dep = py::dict<node_t, bool>{};
    for (auto net : H.nets)
    {
        matchset[net] = false;
        weight[net] = 1;
    }
    for (auto v : H.modules)
    {
        dep[v] = false;
    }
    const auto rslt =
        pldl::min_maximal_matching(H, weight, matchset, dep);
    CHECK(rslt == 3);
}


