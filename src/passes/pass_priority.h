#pragma once

namespace ionir {
    enum class PassPriority {
        /**
         * Highest priority. This precendence
         * will be executed first.
         */
            Important,

        Normal,

        Low,

        Lowest
    };
}
