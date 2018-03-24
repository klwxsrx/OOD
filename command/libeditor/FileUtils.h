#pragma once

namespace FileUtils
{
	void CopyFile(boost::filesystem::path const& from, boost::filesystem::path const& to);
	void DeleteFile(boost::filesystem::path const& path);
	void CreateDirReqursively(boost::filesystem::path const& path);
	bool Exists(boost::filesystem::path const& path);
	std::string GenerateUniqueFileName(boost::filesystem::path const& oldName);
}