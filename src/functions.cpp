// [[Rcpp::plugins(cpp11)]]
#include <Rcpp.h>
#include <string>
using namespace Rcpp;

const auto& R_CLASS_ATTRIB = Rf_mkString("class");
const auto& R_NAMES_ATTRIB = Rf_mkString("names");

// [[Rcpp::export]]
void set_attr(SEXP x, SEXP attr, SEXP value) {
  Rf_setAttrib(x, attr, value);
}

// [[Rcpp::export]]
void set_class(SEXP x, SEXP value) {
  Rf_setAttrib(x, R_CLASS_ATTRIB, value);
}

// [[Rcpp::export]]
void set_names(SEXP x, SEXP value) {
  Rf_setAttrib(x, R_NAMES_ATTRIB, value);
}

// [[Rcpp::export]]
void add_class(SEXP x, std::string value) {
  CharacterVector old_class = Rf_getAttrib(x, R_CLASS_ATTRIB);
  for (const auto& cls : old_class) {
    if (cls == value) return;
  }
  old_class.push_front(value);
  Rf_setAttrib(x, R_CLASS_ATTRIB, old_class);
}

// [[Rcpp::export]]
void remove_class(SEXP x, std::string value) {
  CharacterVector old_class = Rf_getAttrib(x, R_CLASS_ATTRIB);
  CharacterVector new_class;
  for (const auto& cls : old_class) {
    if (cls != value) {
      new_class.push_back(cls);
    }
  }
  Rf_setAttrib(x, R_CLASS_ATTRIB, new_class);
}
