#pragma once
#include <iostream>
#include <sstream>
#include <string>

/**
 * Redirects std::cerr into a string for the lifetime of the object (RAII). Unlike testing::internal::CaptureStderr it
 * needs no temporary file.
 */
class CerrCapture {
public:
    CerrCapture() : Previous(std::cerr.rdbuf(Buffer.rdbuf())) {}
    ~CerrCapture() { std::cerr.rdbuf(Previous); }
    CerrCapture(const CerrCapture&) = delete;
    CerrCapture& operator=(const CerrCapture&) = delete;

    /** Everything written to std::cerr since the capture started. */
    [[nodiscard]] std::string str() const { return Buffer.str(); }

private:
    std::ostringstream Buffer;
    std::streambuf* Previous;
};
