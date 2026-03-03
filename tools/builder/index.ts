/// Node Modules
import * as fs from 'node:fs';
import * as path from 'node:path';

/// Vendor Modules
import * as esbuild from 'esbuild';

//  PROPERTIES  //

const g_root = path.resolve(__dirname, '..', '..');
const g_output = path.resolve(g_root, 'dist', 'vscode');
const g_package = path.join(g_output, 'package.json');
const g_schemas = path.join(g_output, 'schemas');
const g_license = path.join(g_output, 'LICENSE');
const g_readme = path.join(g_output, 'README.md');
const g_config = path.join(g_output, 'language-configuration.json');
const g_development = process.argv.includes('--development');
const g_options: esbuild.BuildOptions = {
    bundle: true,
    minify: !g_development,
    treeShaking: !g_development,

    platform: 'node',
    external: ['vscode'],
    entryPoints: ['source/vscode/bootstrap.ts'],
    outfile: path.join(g_output, 'extension.js'),

    assetNames: '[name]',
    loader: { '.json': 'file' },
};

//  PRIVATE METHODS  //

/** Handles patching the output "package.json" value. */
const m_patch = async () => {
    // prepare the package and extension objects to be used
    const pkg = JSON.parse(await fs.promises.readFile(g_package, 'utf-8'));
    const extension = JSON.parse(await fs.promises.readFile('configs/extension.json', 'utf-8'));

    // and append in all the details for running the project
    Object.assign(pkg, { main: './extension.js' }, extension);

    // delete some items that are not necessary to be kept
    (delete pkg.scripts, delete pkg.dependencies, delete pkg.devDependencies, delete pkg.$schema);

    // finally update the package file being used
    await fs.promises.writeFile(g_package, JSON.stringify(pkg, undefined, 4));

    // also copy across the language configuration file and schemas
    await fs.promises.copyFile(path.resolve(g_root, 'LICENSE'), g_license);
    await fs.promises.copyFile(path.resolve(g_root, 'configs', 'language.json'), g_config);
    await fs.promises.copyFile(path.resolve(g_root, 'docs', 'internal', 'extension.md'), g_readme);
    await fs.promises.cp(path.resolve(g_root, 'schemas'), g_schemas, { recursive: true, force: true });
};

/** Handles building the project. */
const m_build = async () => {
    const result = await esbuild.build(g_options); // construct the suitable result and printer
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
};

//  TOOL RUNNER  //

(async () => m_build())();
