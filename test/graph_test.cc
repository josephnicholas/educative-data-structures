#include "graph.hpp"
#include "gtest/gtest.h"

using namespace ::testing;

struct GraphTestShould : Test {
  void SetUp() override {
    graph_ = std::make_unique<Graph<int>>(5);
  }

  void TearDown() override {
    graph_.reset();
  }

  std::unique_ptr<Graph<int>> graph_{};
};

TEST_F(GraphTestShould, BePrintable) {
  graph_->add_edge_directed(0, 1);
  graph_->add_edge_directed(0, 2);
  graph_->add_edge_directed(1, 4);
  graph_->add_edge_directed(1, 5);

  EXPECT_TRUE(graph_->print_graph());
}
