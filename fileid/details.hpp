#pragma once

#include <string>
#include <vector>
#include "common.hpp"
#include "oless/oless.hpp"
#include "exe/Exec.hpp"
#include "mp4/mp4.hpp"
#include "zip/ziphelper.hpp"

namespace details {

	std::vector<common::ExtensionInfo*> DwgHelper(const std::string file, std::vector<unsigned char> buffer) {
		std::vector<common::ExtensionInfo*> ans;
		common::ExtensionInfo* ei = new common::ExtensionInfo();
		ei->Extension = "dwg";
		
		if (buffer.size() > 5) {

			if (buffer[4] == 0x30) {
				if (buffer[5] == 0x32)
					ei->VersionName = "AutoCAD R2.5";
				else if (buffer[5] == 0x33)
					ei->VersionName = "AutoCAD R2.6";
				else if (buffer[5] == 0x34)
					ei->VersionName = "AutoCAD R9";
				else if (buffer[5] == 0x36)
					ei->VersionName = "AutoCAD R10";
				else if (buffer[5] == 0x39)
					ei->VersionName = "AutoCAD R11/R12";
			}
			else if (buffer[4] == 0x31) {
				if (buffer[5] == 0x30)
					ei->VersionName = "AutoCAD R13 (subtype 10)";
				else if (buffer[5] == 0x31)
					ei->VersionName = "AutoCAD R13 (subtype 11)";
				else if (buffer[5] == 0x32)
					ei->VersionName = "AutoCAD R13 (subtype 12)";
				else if (buffer[5] == 0x33)
					ei->VersionName = "AutoCAD R14 (subtype 13)";
				else if (buffer[5] == 0x34)
					ei->VersionName = "AutoCAD R14 (subtype 14)";
				else if (buffer[5] == 0x35)
					ei->VersionName = "AutoCAD R2000";
				else if (buffer[5] == 0x38)
					ei->VersionName = "AutoCAD R2004";
			}
			else if (buffer[4] == 0x32) {
				if (buffer[5] == 0x31)
					ei->VersionName = "AutoCAD R2007";
			}
		}
		ans.push_back(ei);
		return ans;
	}
	std::vector<common::ExtensionInfo*> ExeHelper(const std::string file, std::vector<unsigned char> buffer) {
		return Exec::Detailer(file, buffer);
	}
	std::vector<common::ExtensionInfo*> JpegHelper(const std::string file, std::vector<unsigned char> buffer) {
		std::vector<common::ExtensionInfo*> ans;
		common::ExtensionInfo* ei = new common::ExtensionInfo();
		ei->Extension = "jpg";
		ans.push_back(ei);
		return ans;
	}
	std::vector<common::ExtensionInfo*> ASFHelper(const std::string file, std::vector<unsigned char> buffer) {
		std::vector<common::ExtensionInfo*> ans;
		common::ExtensionInfo* ei = new common::ExtensionInfo();
		ei->Extension = "asf";
		ans.push_back(ei);
		return ans;
	}
	std::vector<common::ExtensionInfo*> RIFFHelper(const std::string file, std::vector<unsigned char> buffer) {
		std::vector<common::ExtensionInfo*> ans;
		unsigned char magic_cda[8] = { 0x43, 0x44, 0x44, 0x41, 0x66, 0x6D, 0x74, 0x20 }; //at offset 8, only if magic_riff
		unsigned char magic_wav[8] = { 0x57, 0x41, 0x56, 0x45, 0x66, 0x6D, 0x74, 0x20 }; //at offset 8, only if magic_riff
		unsigned char magic_avi[8] = { 0x41, 0x56, 0x49, 0x20, 0x4C, 0x49, 0x53, 0x54 }; //at offset 8, only if magic_riff
		unsigned char magic_qcp[8] = { 0x51, 0x4C, 0x43, 0x4D, 0x66, 0x6D, 0x74, 0x20 }; //at offset 8, only if magic_riff
		unsigned char magic_rmi[8] = { 0x52, 0x4D, 0x49, 0x44, 0x64, 0x61, 0x74, 0x61 }; //at offset 8, only if magic_riff
		common::ExtensionInfo* ei = new common::ExtensionInfo();

		if (common::checkMagic(buffer.data(), 8, magic_cda, 8, 8))
			ei->Extension = "cda";
		else if (common::checkMagic(buffer.data(), 8, magic_wav, 8, 8))
			ei->Extension = "wav";
		else if (common::checkMagic(buffer.data(), 8, magic_avi, 8, 8))
			ei->Extension = "avi";
		else if (common::checkMagic(buffer.data(), 8, magic_qcp, 8, 8))
			ei->Extension = "qcp";
		else if (common::checkMagic(buffer.data(), 8, magic_rmi, 8, 8))
			ei->Extension = "rmi";
		else
			ei->Extension = "riff";

		ans.push_back(ei);
		return ans;
	}
		
	std::vector<common::ExtensionInfo*> Mp4Helper(const std::string file, std::vector<unsigned char> buffer) {
		std::vector<common::ExtensionInfo*> ans;
		common::ExtensionInfo* ei = mp4::Detailer(file, buffer);
		ans.push_back(ei);
		return ans;
	}
	std::vector<common::ExtensionInfo*> OleHelper(const std::string file, std::vector<unsigned char> buffer) {
		OleStructuredStorage::Oless* o = new OleStructuredStorage::Oless(file.c_str());
		return o->Guess();		
	}
	std::vector<common::ExtensionInfo*> ZipHelper(const std::string file, std::vector<unsigned char> buffer) {
		return zip::Detailer(file, buffer);
	}


}
