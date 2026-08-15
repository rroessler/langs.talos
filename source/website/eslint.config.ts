/// Vendor Modules
import * as eslint from 'eslint/config';
import typescript from 'eslint-config-next/typescript';
import vitals from 'eslint-config-next/core-web-vitals';

/** ESLint Configuration. */
export default eslint.defineConfig([
    // bind the defaulted details to be used
    ...vitals,
    ...typescript,

    // define some next ignore paths
    eslint.globalIgnores(['.next/**', 'out/**', 'build/**', '.source/**', 'next-env.d.ts']),

    {
        // Fix for ESLint 10+: eslint-plugin-react uses context.getFilename() (legacy API)
        // which was removed in ESLint 10 flat config. Declaring the version explicitly
        // prevents the plugin from trying to auto-detect it and failing.
        settings: { react: { version: '19' } },

        // defining our own collection of rules that we allow
        rules: {
            'react/no-children-prop': 'off',
            '@typescript-eslint/no-namespace': 'off',
            '@typescript-eslint/no-explicit-any': 'off',
            '@typescript-eslint/no-empty-object-type': 'off',
        },
    },
]);
