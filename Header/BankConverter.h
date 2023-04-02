#pragma once
#include <filesystem>

struct E4Result;

struct ConverterOptions final
{
	ConverterOptions() noexcept = default;
	explicit ConverterOptions(const bool flipPan, const bool useConverterSpecificData, const bool useTempFineTune)
		: m_flipPan(flipPan), m_useConverterSpecificData(useConverterSpecificData), m_useTempFineTune(useTempFineTune) {}

	bool m_flipPan = false;
	bool m_useConverterSpecificData = true;
	bool m_useTempFineTune = false;
	std::filesystem::path m_saveFolder;
};

namespace SF2Converter
{
	/*
	* Converter specific
	*/

	// kUnused1 = LFO1 ~ -> Amp Pan
	// kUnused2 = Positive or negative attenuation
	// kUnused3 = LFO1 shape
	// kUnused4 = LFO1 Key Sync
	// kUnused5 = Chorus Width

	constexpr auto SF2_MAX_NAME_LEN = 20u;
	constexpr auto BASE_CENT_VALUE = 6900i16;
	constexpr auto SF2_FILTER_MIN_FREQ = 1500i16;
	constexpr auto SF2_FILTER_MAX_FREQ = 13500i16;
	constexpr auto MIN_MAX_LFO1_TO_VOLUME = 15.f;
	constexpr auto MAX_FILTER_FREQ_HZ_CORDS(12000.f);
	constexpr auto MAX_SUSTAIN_VOL_ENV = 144.f;

	[[nodiscard]] int16_t filterFreqPercentToCents(float filterFreq);
	[[nodiscard]] float centsToFilterFreqPercent(int16_t cents);
	[[nodiscard]] int16_t secToTimecent(double sec);
}

struct BankConverter final
{
	[[nodiscard]] bool ConvertE4BToSF2(const E4Result& e4b, const std::string_view& bankName, const ConverterOptions& options = {}) const;
	[[nodiscard]] bool ConvertSF2ToE4B(const std::filesystem::path& bank, const std::string_view& bankName, const ConverterOptions& options = {}) const;
private:
	[[nodiscard]] std::string ConvertNameToEmuName(const std::string_view& name) const;
	[[nodiscard]] std::string ConvertNameToSFName(const std::string_view& name) const;

	void InterleaveSamples(const int16_t* leftChannel, const int16_t* rightChannel, int16_t* outStereo, size_t sampleNum) const;
};