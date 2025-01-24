#include "parser.h"

namespace s21 {
void VertexParser::parser(const std::string &line) const {
  Point_3D vertex{};
  sscanf(line.c_str() + 2, "%f %f %f", &vertex.x_, &vertex.y_, &vertex.z_);
  model_.vertices_.emplace_back(std::move(vertex));
}

void EdgeParser::parser(const std::string &line) const {
  Edge face{};
  const char *cstr = line.c_str() + 2;
  int vertex_index;
  while (sscanf(cstr, "%d", &vertex_index) == 1) {
    face.vertex_indices.emplace_back(vertex_index);
    while (*cstr && *cstr != ' ') ++cstr;
    if (*cstr) ++cstr;
  }
  model_.faces_.emplace_back(std::move(face));
}

void ParseModel::setStrategy(std::unique_ptr<VirtualParser> &&strategy) {
  currentStrategy_ = std::move(strategy);
}

void ParseModel::loadModel(Model &model, const std::string &filename) {
  std::ifstream infile(filename);
  if (!infile.is_open()) {
    std::cerr << "Error opening file" << std::endl;
    return;
  } else {
    std::string line;
    while (std::getline(infile, line)) {
      if (line.substr(0, 2) == "v ") {
        setStrategy(std::make_unique<VertexParser>(model));
        currentStrategy_->parser(line);
      } else if (line.substr(0, 2) == "f ") {
        setStrategy(std::make_unique<EdgeParser>(model));
        currentStrategy_->parser(line);
      }
    }
    infile.close();
  }
}
}  // namespace s21
