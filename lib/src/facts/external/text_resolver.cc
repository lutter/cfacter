#include <facter/facts/external/text_resolver.hpp>
#include <facter/facts/fact_map.hpp>
#include <facter/facts/scalar_value.hpp>
#include <facter/logging/logging.hpp>
#include <facter/util/file.hpp>
#include <facter/util/string.hpp>

using namespace std;
using namespace facter::util;

LOG_DECLARE_NAMESPACE("facts.external.text");

namespace facter { namespace facts { namespace external {

    bool text_resolver::resolve(string const& path, fact_map& facts) const
    {
        string full_path = path;
        if (!ends_with(to_lower(full_path), ".txt")) {
            return false;
        }

        LOG_DEBUG("resolving facts from text file \"%1%\".", path);

        if (!file::each_line(path, [&facts](string& line) {
            auto pos = line.find('=');
            if (pos == string::npos) {
                LOG_DEBUG("ignoring line in output: %1%", line);
                return true;
            }
            // Add as a string fact
            facts.add(line.substr(0, pos), make_value<string_value>(line.substr(pos+1)));
            return true;
        })) {
            throw external_fact_exception("file could not be opened.");
        }

        LOG_DEBUG("completed resolving facts from text file \"%1%\".", path);
        return true;
    }

}}}  // namespace facter::facts::external
