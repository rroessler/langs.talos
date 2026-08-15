/// Node Modules
import * as fs from 'node:fs';

/// Vendor Modules
import * as types from 'type-fest';
import * as esbuild from 'esbuild';

/// Tool Modules
import { Assets } from '~/tools/assets/index';

/// JSON Modules
import MONOREPO from '~/package.json';
import EXTENSION from '~/configs/extension.json';

//  TOOL RUNNER  //

/// Run the core builder instance.
(async () => m_build())();

//  PRIVATE METHODS  //

/** Gets the available options. */
function m_options(): esbuild.BuildOptions {
    // check if running in development mode
    const development = process.argv.includes('--development');

    return {
        bundle: true,
        minify: !development,
        treeShaking: !development,

        platform: 'node',
        external: ['vscode'],
        assetNames: '[name]',
        entryPoints: ['library/bootstrap.ts'],
        outfile: Assets.vscode('extension.js'),
    };
}

/** Handles patching the output "package.json" value. */
async function m_patch() {
    // prepare the directories and details to be use

    // prepare the baseline extension "package.json"
    const inject = { main: 'extension.js', version: MONOREPO.version };
    const pkg = Object.assign({}, inject, EXTENSION) as unknown as types.PackageJson;

    // delete some items that are not necessary to be kept
    (delete pkg.scripts, delete pkg.dependencies, delete pkg.devDependencies, delete pkg.$schema);

    // finally update the package file being used
    await fs.promises.writeFile(Assets.vscode('package.json'), JSON.stringify(pkg, undefined, 4));

    // also copy across the language configuration file and schemas
    await fs.promises.copyFile(Assets.root('LICENSE'), Assets.vscode('LICENSE'));
    await fs.promises.copyFile(Assets.configs('language.json'), Assets.vscode('language-configuration.json'));
    await fs.promises.copyFile(Assets.root('docs', 'internal', 'extension.md'), Assets.vscode('README.md'));
    await fs.promises.cp(Assets.root('schemas'), Assets.vscode('schemas'), { recursive: true, force: true });
}

/** Handles building the project. */
async function m_build() {
    const result = await esbuild.build(m_options()); // construct the suitable result and printer
    const printer = (messages: string[]) => messages.forEach((message) => console.log(message));

    // display any error or warnsing that occured
    const errors = esbuild.formatMessages(result.errors, { kind: 'error' }).then(printer);
    const warnings = esbuild.formatMessages(result.warnings, { kind: 'warning' }).then(printer);

    // check the total errors count
    const failed = !!result.errors.length;

    // show the errors and warnings concurrently
    await Promise.all([errors, warnings]);

    // post-patch the "package.json" file
    if (!failed) await m_patch();

    // and exit as necessary now
    process.exit(+failed);
}
