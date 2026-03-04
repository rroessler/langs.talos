/// Node Modules
import * as fs from 'node:fs';
import * as path from 'node:path';
import * as cp from 'node:child_process';

/// Vendor Modules
import * as YAML from 'yaml';
import * as JSONC from 'jsonc-parser';

//  PROPERTIES  //

const g_root_dir = process.cwd();
const g_examples_dir = path.resolve(g_root_dir, 'examples');
const g_crates_dir = path.resolve(g_root_dir, 'source', 'crates');
const g_version_path = path.resolve(g_root_dir, 'configs', 'version.txt');
const g_version_nightly = cp.execSync('git branch --show-current').toString().trim() === 'nightly';
const g_version_text = fs.readFileSync(g_version_path, 'utf-8').trim() + `${g_version_nightly ? '-nightly' : ''}`;

const g_targets: string[] = [
    path.resolve(g_root_dir, '_crate.jsonc'),
    path.resolve(g_root_dir, 'package.json'),
    ...fs
        .readdirSync(g_crates_dir)
        .concat([g_examples_dir])
        .map((name) => path.resolve(g_crates_dir, name, '_crate.jsonc')),
];

//  PRIVATE METHODS  //

/**
 * Handles parsing details.
 * @param extension                 Extension to handle.
 * @param content                   Content to parse.
 */
function m_parse(extension: string, content: string): any {
    switch (extension) {
        case '.yaml': return YAML.parse(content); // prettier-ignore
        case '.json': return JSON.parse(content); // prettier-ignore
        case '.jsonc': return JSONC.parse(content); // prettier-ignore
        default: throw new Error(`Invalid file-extension: ${extension}`); // prettier-ignore
    }
}

/**
 * Handles stringifying details.
 * @param extension                 Extension to handle.
 * @param details                   Details to stringify.
 */
function m_stringify(extension: string, details: any): string {
    switch (extension) {
        case '.yaml': return YAML.stringify(details); // prettier-ignore
        case '.json': return JSON.stringify(details, null, 4); // prettier-ignore
        case '.jsonc':  return JSON.stringify(details, null, 4); // prettier-ignore
        default: throw new Error(`Invalid file-extension: ${extension}`); // prettier-ignore
    }
}

/**
 * Handles replacing files version values.
 * @param target                   Target to update.
 */
async function m_replace(target: string) {
    // ignore if the file does not actually exist
    if (!fs.existsSync(target)) return;

    // get the associated extension value
    const extension = path.extname(target);
    const parse = m_parse.bind(undefined, extension);
    const stringify = m_stringify.bind(undefined, extension);

    // prepare the base outputs to be used
    const details: any = await fs.promises.readFile(target, 'utf-8').then(parse);

    // update and replace as necessary now
    details.version = g_version_text;

    // rebuild the output content now
    await fs.promises.writeFile(target, stringify(details) + '\n');
}

//  TOOL RUNNER  //

(async () => {
    console.log(`Setting Version: '${g_version_text}'`);
    await Promise.all(g_targets.map(m_replace));
})();
