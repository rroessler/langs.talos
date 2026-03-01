/// Node Modules
import * as fs from 'node:fs';
import * as path from 'node:path';

/// Vendor Modules
import * as YAML from 'yaml';

//  PROPERTIES  //

/** Get the root-directory. */
const g_root = path.resolve(__dirname, '..', '..');

/** Output directory name. */
const g_outdir = path.resolve(g_root, 'dist', 'vscode', 'syntaxes');

const g_injection = 'talos.injection.json'; // prepare injection
const g_destination = path.resolve(g_outdir, 'talos.tmLanguage.json');
const g_source = path.resolve(g_root, 'syntaxes', 'talos.tmLanguage.yaml');

//  TOOL RUNNER  //

(async () => {
    // get the underlying content to be emitted
    const content = YAML.parse(await fs.promises.readFile(g_source, 'utf-8'));

    // ensure the destination actually exists now
    if (!fs.existsSync(g_outdir)) await fs.promises.mkdir(g_outdir, { recursive: true });

    // and write the resulting content now
    await fs.promises.writeFile(g_destination, JSON.stringify(content, undefined, 4));

    // also copy the injection syntax to be used as well
    await fs.promises.copyFile(path.resolve('syntaxes', g_injection), path.resolve(g_outdir, g_injection));
})();
