#pragma once

template < typename var >
class gmvar {
 public:
   var value;
   inline gmvar() : value(var(0.f)) {
   }
   inline gmvar(var initialValue) : value(initialValue) {
   }

   gmvar< var > &operator=(var value) {
      this->value = value;
      return *this;
   }

   inline gmvar operator+(const gmvar< var > &other) const {
      gmvar result;
      result.value = (var)value + other.value;
      return result;
   }

   inline gmvar operator-(const gmvar< var > &other) const {
      gmvar result;
      result.value = value - other.value;
      return result;
   }

   inline var operator*(const gmvar< var > &other) {
      return value * (var)other.value;
   }


   inline gmvar< var > operator/(const gmvar< var > &other) const {
      gmvar result;
      if (other.value != 0.0) {
         result.value = value / other.value;
      }
      else {
         result.value = 0.0;
      }
      return result;
   }
   //

   inline gmvar< var > &operator+=(const gmvar< var > &other) {
      value += (var)other.value;
      return *this;
   }


   inline gmvar< var > &operator-=(const gmvar< var > &other) {
      value -= (var)other.value;
      return *this;
   }

   inline gmvar< var > &operator*=(const gmvar< var > &other) {
      value *= (var)other.value;
      return *this;
   }


   inline gmvar< var > &operator/=(const gmvar< var > &other) {
      if (other.value != 0.0) {
         value /= other.value;
      }
      else {
      }

      return *this;
   }

   template < typename v >
   inline gmvar operator/=(v ovalue) {
      this->operator/=(gmvar(ovalue));
      return *this;
   }

   template < typename v >
   inline gmvar operator=(v ovalue) {
      return this->operator=(gmvar(ovalue));
   }

   template < typename v >
   inline gmvar operator*=(v ovalue) {
      this->operator*=(gmvar(ovalue));
      return *this;
   }

   template < typename v >
   inline v operator*(v ovalue) const {
      return this->operator*(gmvar(ovalue));
   }

   template < typename v >
   inline gmvar operator+(v ovalue) const {
      return this->operator+(gmvar(ovalue));
   }

   template < typename v >
   inline gmvar operator-(v ovalue) const {
      return this->operator-(gmvar(ovalue));
   }

   template < typename v >
   inline gmvar operator/(v ovalue) const {
      if (ovalue != 0.0) {
         return value / ovalue;
      }
      else {
         return 0.0;
      }
   }

   inline bool operator==(  gmvar< var > &other)  {
      return value == (var)other.value;
   }

   inline bool operator!=( gmvar< var > &other)   {
      return value != (var)other.value;
   }

   inline bool operator>=(  gmvar< var > &other)   {
      return value >= (var)other.value;
   }

   inline bool operator<=(  gmvar< var > &other )   {
      return value <= (var)other.value;
   }
   inline bool operator>(  gmvar< var > &other)   {
      return value > (var)other.value;
   }

   inline bool operator<(  gmvar< var > &other)   {
      return value < (var)other.value;
   }
   

   template < typename primitive >
   inline bool operator!=(primitive other) {
      return value != other;
   }

   template < typename primitive >
   inline bool operator>=(primitive other)  {
      return value >= other;
   }

   template < typename primitive >
   inline bool operator<=(primitive other)   {
      return (primitive)value <= other;
   }

   template < typename primitive >
   inline bool operator>(primitive other)   {
      return primitive(value)  >  other;
   }

   template < typename primitive >
   inline bool operator<(primitive other)  {
      return primitive(value) <   other;
   }

   template < typename primitive >
   inline bool operator==(primitive other)  {
      return value == other;
   }

   inline bool operator++(int) {
      value++;
      return 0;
   }

   inline gmvar< var > &operator--(int) {
      value--;
      return *this;
   }

   template < typename T >
   gmvar< var > operator/=(T value) const {
      if (value != 0) {
         this->value /= var(value);
      }
      else {
      }
      return *this;
   }

   operator int() {
      return (int)value;
   }
   operator float() {
      return float(value);
   }
   operator double() {
      return double(value);
   }
   ~gmvar() {
   }
};
