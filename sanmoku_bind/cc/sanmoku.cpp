//
// Created by KHML on 2020/07/31.
//

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <py_board.hpp>

namespace py = pybind11;

PYBIND11_MODULE(ccsanmoku, m)
{
    m.doc() = "Python Sanmoku Module implemented by C++";

    py::enum_<sanmoku::Color>(m, "Color")
        .value("Empty", sanmoku::Empty)
        .value("Cycle", sanmoku::Circle)
        .value("Cross", sanmoku::Cross)
        .value("OutOfRange", sanmoku::OutOfRange)
        .export_values();

    py::class_<sanmoku::Move>(m, "Move")
        .def(py::init<const sanmoku::Color&, const int&>())
        .def_readonly("color", &sanmoku::Move::color)
        .def_readonly("pos", &sanmoku::Move::pos);

    py::class_<PyBoard>(m, "Board")
        .def(py::init())
        .def("put", &PyBoard::put, "put(const int pos, const bool isCross)")
        .def("asList", &PyBoard::getBoard)
        .def("isLegal", &PyBoard::isLegal, "isLegal(const int pos)")
        .def("isFinished", &PyBoard::isFinished)
        .def("result", &PyBoard::result);
}


