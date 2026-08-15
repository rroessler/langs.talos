/// Vendor Includes
#include <boost/interprocess/file_mapping.hpp>
#include <boost/interprocess/mapped_region.hpp>

/// Library Includes
#include "xtdlib/filesystem/read.hpp"

/// Forward Definitions
$_FWD($::FS::Buffer, using Offset = boost::interprocess::offset_t)
$_FWD($::FS::Buffer, using Mapping = boost::interprocess::file_mapping)
$_FWD($::FS::Buffer, using Region = boost::interprocess::mapped_region)

/// Forward Declarations
$_FWD($::FS::Buffer, Offset Size(Mapping &, Offset = 0))
$_FWD($::FS::Buffer, Region Resolve(const String::View &))

//  CONSTRUCTORS  //

$::String::Buffer $::FS::Read(const String::Buffer &buffer) { return Read(String::View(buffer)); }
$::String::Buffer $::FS::Read(const FS::Path &file_path) { return Read(file_path.string()); }
$::String::Buffer $::FS::Read(const String::View &file_path) {
  auto region = Buffer::Resolve(file_path); // prepare region to be mapped
  return {static_cast<const char *>(region.get_address()), region.get_size()};
}

std::vector<uint8_t> $::FS::Bytes(const String::Buffer &buffer) { return Bytes(String::View(buffer)); }
std::vector<uint8_t> $::FS::Bytes(const FS::Path &file_path) { return Bytes(file_path.string()); }
std::vector<uint8_t> $::FS::Bytes(const String::View &file_path) {
  auto region = Buffer::Resolve(file_path); // prepare region
  auto start = static_cast<const uint8_t *>(region.get_address());
  return {start, start + region.get_size()}; // baseline here
}

//  PUBLIC METHODS  //

$::FS::Buffer::Region $::FS::Buffer::Resolve(const String::View &file_path) {
  try {
    static constexpr auto readonly = boost::interprocess::read_only;
    auto mapping = Mapping(file_path.data(), readonly); // attempt
    return Size(mapping) ? Region(mapping, readonly) : Region();
  } catch (...) {
    $_ERROR("FS::Buffer / Invalid file-mapping - {0}", file_path);
    std::rethrow_exception(std::current_exception()); // re-throw
  }
}

$::FS::Buffer::Offset $::FS::Buffer::Size(Mapping &mapping, Offset size) {
  return boost::interprocess::ipcdetail::get_file_size(mapping.get_mapping_handle().handle, size), size;
}
