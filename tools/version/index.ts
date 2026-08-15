/// Node Modules
import * as fs from 'node:fs';
import * as path from 'node:path';
import * as cp from 'node:child_process';

/// Vendor Modules
import * as YAML from 'yaml';
import * as JSONC from 'jsonc-parser';
import * as TYPES from 'type-fest';

/// Tool Modules
import { Assets } from '@/tools/assets';

//  PRIVATE METHODS  //

/** Resolves the current version to assign. */
function m_version() {
    const nightly = cp.execSync('git branch --show-current').toString().trim() === 'nightly';
    return fs.readFileSync(Assets.configs('version.txt'), 'utf-8').trim() + `${nightly ? '-nightly' : ''}`;
}

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
 * @param version                  Version to assign.
 * @param target                   Target to update.
 */
async function m_replace(version: string, target: string) {
    // ignore if the file does not actually exist
    if (!fs.existsSync(target)) return;

    // get the associated extension value
    const extension = path.extname(target);
    const parse = m_parse.bind(undefined, extension);
    const stringify = m_stringify.bind(undefined, extension);

    // prepare the base outputs to be used
    const details: TYPES.PackageJson = await fs.promises.readFile(target, 'utf-8').then(parse);

    // update and replace as necessary now
    details.version = version;

    // rebuild the output content now
    await fs.promises.writeFile(target, stringify(details) + '\n');
}

//  TOOL RUNNER  //

(async () => {
    // get the current version to be assigned
    const version = m_version();

    // note to the user what version we are assigning now
    console.log(`Setting Version: '${version}'`);

    // prepare all the crate files to be targeted
    const crates = fs
        .readdirSync(Assets.crates())
        .concat([Assets.examples()])
        .map((name) => path.resolve(Assets.crates(), name, '_crate.jsonc'));

    /// TODO: prepare all the source packages to resolve

    // prepare all the necessary targets to be replaced
    const targets = [Assets.root('_crate.jsonc'), Assets.root('package.json')].concat(crates);

    // and attempt replacing all the necessary targets now
    await Promise.all(targets.map(m_replace.bind(undefined, version)));
})();
