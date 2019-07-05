#include "../src/Board.hpp"
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

using sanmoku::Color;
using sanmoku::Empty;
using sanmoku::Cycle;
using sanmoku::Cross;
using sanmoku::OutOfRange;
using sanmoku::Move;
using sanmoku::Board;

namespace py = pybind11;


PYBIND11_MODULE(ccsanmoku, m)
{
    m.doc() = "Python Sanmoku Module implemented by C++";

    py::enum_<Color>(m, "Color")
            .value("Empty", Empty)
            .value("Cycle", Cycle)
            .value("Cross", Cross)
            .value("OutOfRange", OutOfRange)
            .export_values();

    py::class_<Move>(m, "Move")
            .def(py::init<const Color &, const int &>())
            .def_readonly("color", &Move::color)
            .def_readonly("pos", &Move::pos);

    py::class_<Board>(m, "Board")
            .def(py::init())
            .def("put", &Board::put, "put(const int pos, const bool isCross)")
            .def("asList", &Board::getBoard)
            .def("isLegal", &Board::isLegal, "isLegal(const int pos)")
            .def("isFinished", &Board::isFinished)
            .def_readonly("result", &Board::result);
}
