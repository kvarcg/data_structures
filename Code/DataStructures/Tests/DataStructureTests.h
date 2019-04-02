#ifndef DSDATASTRUCTURETESTS_H
#define DSDATASTRUCTURETESTS_H

#pragma once
//using namespace

// includes ////////////////////////////////////////
#include <cstdint>

// defines /////////////////////////////////////////


// forward declarations ////////////////////////////


// class declarations //////////////////////////////

namespace DS {
#ifdef DS_DEBUG_LOG_VERBOSE
	struct GenericTestObject {
		int64_t val;
		double v;
        GenericTestObject(int64_t v1) : val(v1), v(-10.0) {
			X_DEBUG_COMMENT("Explicit Constructor 0x%p with val: %d", this, val);
        }
		GenericTestObject() : GenericTestObject(0) {
			X_DEBUG_COMMENT("Default Constructor 0x%p with val: %d", this, val);
		}
		~GenericTestObject() {
			X_DEBUG_COMMENT("Destructor 0x%p with val: %d", this, val);
			val = -1;
			v = -1.0f;
		};
		GenericTestObject(const GenericTestObject& other) {
			v = other.v;
			val = other.val;
			X_DEBUG_COMMENT("Copy Constructor 0x%p with val: %d", this, val);
		};
		GenericTestObject& operator=(const GenericTestObject& other) {
			if (this != &other) {
				v = other.v;
				val = other.val;
			}
			X_DEBUG_COMMENT("Copy Assignment 0x%p with val: %d", this, val);
			return *this;
		};
		GenericTestObject(GenericTestObject&& other) {
			v = other.v;
			val = other.val;
			X_DEBUG_COMMENT("Move Constructor 0x%p with val: %d", this, val);
		};
		GenericTestObject& operator=(GenericTestObject&& other) {
			if (this != &other) {
				v = other.v;
				val = other.val;
			}
			X_DEBUG_COMMENT("Move Assignment 0x%p with val: %d", this, val);
			return *this;
		};
		friend bool operator==(const GenericTestObject& lhs, const GenericTestObject& rhs) { return lhs.val == rhs.val; }
		friend bool operator!=(const GenericTestObject& lhs, const GenericTestObject& rhs) { return !(lhs == rhs); }
		friend bool operator<(const GenericTestObject& lhs, const GenericTestObject& rhs) { return lhs.val < rhs.val; }
		friend bool operator<=(const GenericTestObject& lhs, const GenericTestObject& rhs) { return lhs.val <= rhs.val; }
		friend bool operator>(const GenericTestObject& lhs, const GenericTestObject& rhs) { return !(lhs.val <= rhs.val); }
		friend bool operator>=(const GenericTestObject& lhs, const GenericTestObject& rhs) { return !(lhs.val < rhs.val); }
	};
#else
	struct GenericTestObject {
		int64_t val;
		double v;
		GenericTestObject(int64_t v1) : val(v1), v(-10.0) { }
		//explicit GenericTestObject(uint64_t v1) : val(static_cast<int64_t>(v1)), v(-10.0) { }
		GenericTestObject() : GenericTestObject(0) {}
		~GenericTestObject() { val = -1; v = -1.0f; }
		GenericTestObject(const GenericTestObject&) = default;
		GenericTestObject& operator=(const GenericTestObject&) = default;
		GenericTestObject(GenericTestObject&&) = default;
		GenericTestObject& operator=(GenericTestObject&&) = default;
		friend bool operator==(const GenericTestObject& lhs, const GenericTestObject& rhs) { return lhs.val == rhs.val; }
		friend bool operator!=(const GenericTestObject& lhs, const GenericTestObject& rhs) { return !(lhs == rhs); }
		friend bool operator<(const GenericTestObject& lhs, const GenericTestObject& rhs) { return lhs.val < rhs.val; }
		friend bool operator<=(const GenericTestObject& lhs, const GenericTestObject& rhs) { return lhs.val <= rhs.val; }
		friend bool operator>(const GenericTestObject& lhs, const GenericTestObject& rhs) { return !(lhs.val <= rhs.val); }
		friend bool operator>=(const GenericTestObject& lhs, const GenericTestObject& rhs) { return !(lhs.val < rhs.val); }
	};
#endif
}
#endif //DSDATASTRUCTURETESTS_H

